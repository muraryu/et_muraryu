/******************************************************************************
 *  GarageRApproachState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/23
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  コースR（フィギュア側）ゴール接近
 *  グレーライン検知でゴール距離を再設定して次に遷移
 *  グレーライン検出失敗時はフィギュア段差下りからの距離で遷移
 *  Author: muraryu
 *****************************************************************************/

#include "GarageRApproachState.h"

#include "util/Bluetooth.h"
#include "control_state/GarageSitDownState.h"

/**
 * コンストラクタ
 */
GarageRApproachState::GarageRApproachState() {

	Bluetooth::sendMessage("State changed : GarageRApproachState\n", 38);

	// シングルトンインスタンス取得
	this->balancingWalker = BalancingWalker::getInstance();
	this->tail = Tail::getInstance();
	this->postureEstimation = PostureEstimation::getInstance();
	this->lineMonitor = LineMonitor::getInstance();
	this->time = Time::getInstance();

	// インスタンス生成
	this->pidTurn = new PID(5,0,0);

	// 初期処理
	this->startDirection = this->postureEstimation->getDirection();
	this->figureEndFlag = false;
	this->balancingWalker->notifyGarageDistance(10000); // ガレージまでの距離を適当に大きい値で初期化
	this->figureEndTime = 999;							// フィギュア下り段差の時刻を適当に大きな値で初期化
}

/**
 * デストラクタ
 */
GarageRApproachState::~GarageRApproachState() {
	delete this->pidTurn;
}

/**
 * 制御ステートに応じた制御を実行
 */
void GarageRApproachState::execute() {

	int forward = 40;
	int turn = 0;
	int angle = 0;

	/* 足の制御 */
	// 前進値、旋回値を設定
	if(this->figureEndFlag == false) { // フィギュアL段差下りの少し先までは真っ直ぐ進む
		turn = (int)this->pidTurn->calc(this->startDirection,this->postureEstimation->getDirection(),-30,30);
	}
	else { // 段差後すこし進んだらライントレース再開
		this->pidTurn->setPID(80,0,1200);
		turn = (int)-this->pidTurn->calc(0.7,this->lineMonitor->getAdjustedBrightness(),-100,100);
	}
	if(this->balancingWalker->calcGarageDistance() < 800) { // 段差を降りて少ししたらスピードダウン test1030
		forward = 15;
	}
	// 足の制御実行
	balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
	if(this->balancingWalker->calcGarageDistance() < 800) { // しばらく走ったらしっぽを途中までおろしておく test1030
		angle = 80;
	}

	// しっぽの制御実行
	this->tail->setCommandAngle(angle);

	//Bluetooth::sendMessage(this->postureEstimation->getDirection() - this->startDirection);
}

/**
 * 制御ステート遷移条件
 * @return	ControlState* 遷移先クラスインスタンス
 * @note	遷移しないときはthisを返す
 */
ControlState* GarageRApproachState::next() {

	//Bluetooth::sendMessage(this->balancingWalker->getLeftAngularVelocity() * 1000 + this->balancingWalker->getRightAngularVelocity());
	// フィギュアL段差下りを検出して位置を記録
	if(this->figureEndFlag == false && 350 < this->balancingWalker->getLeftAngularVelocity() && 350 < this->balancingWalker->getRightAngularVelocity() ) {
		this->figureEndFlag = true;
		this->balancingWalker->notifyGarageDistance(1070); //TODO 当日調整 段差からガレージまでの距離 test用=1300 試走会２=1070
		this->figureEndTime = this->time->getTime();
	}

	//Bluetooth::sendMessage(this->balancingWalker->calcGarageDistance());

	// グレーを検知できたときはその位置からガレージまでの残りの距離を再設定して遷移
	if(1.5 < this->time->getTime() - this->figureEndTime && this->lineMonitor->getGrayFound() == true) {
		Bluetooth::sendMessage("Found Gray. Re-set Garage Distance.\n", 37);
		this->balancingWalker->notifyGarageDistance(450); //TODO 当日調整 グレー見つけたとき残りの距離を再設定
		return new GarageSitDownState();
	}

	// ガレージまでの距離がゼロで遷移
	if(this->balancingWalker->calcGarageDistance() < 0) {
		return new GarageSitDownState();
	}

	return this;
}
