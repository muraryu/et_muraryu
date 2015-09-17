/******************************************************************************
 *  GarageLApproachState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/23
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  コースL（ルックアップ側）ゴール接近
 *  グレーライン検知でゴール距離を再設定して次に遷移
 *  グレーライン検出失敗時はゲートからの距離で遷移
 *  Author: muraryu
 *****************************************************************************/

#include "GarageLApproachState.h"

#include "util/Bluetooth.h"
#include "control_state/GarageSitDownState.h"

/**
 * コンストラクタ
 */
GarageLApproachState::GarageLApproachState() {

	Bluetooth::sendMessage("State changed : GarageLApproachState\n", 38);

	// メンバ初期化
	this->balancingWalker = BalancingWalker::getInstance();
	this->tail = Tail::getInstance();
	this->lineMonitor = LineMonitor::getInstance();
	this->postureEstimation = PostureEstimation::getInstance();
	this->time = Time::getInstance();

	// インスタンス生成
	this->pidTurn = new PID(80,0,1200);
	this->pidForward = new PID(0.2,0,0);

	// 初期処理
	this->startDirection = this->postureEstimation->getDirection();
	this->startTime = this->time->getTime();
	this->startRightEnc = this->balancingWalker->getRightEnc();

}

/**
 * デストラクタ
 */
GarageLApproachState::~GarageLApproachState() {
	delete this->pidTurn;
	delete this->pidForward;
}

/**
 * 制御ステートに応じた制御を実行
 */
void GarageLApproachState::execute() {

	int forward = 0;
	int turn = 0;
	int angle = 80;
	double direction = 0;

	/* 足の制御 */
	// 前進値、旋回値を設定
	if(this->time->getTime() - this->startTime < 1.0) { // 1秒待機して安定させる （ディレクション計算のため必須）
		forward = (int)this->pidForward->calc(this->startRightEnc, this->balancingWalker->getRightEnc(), -100, 100);
		this->startDirection = this->postureEstimation->getDirection();
	}
	else { // 1秒後からライントレース
		forward = 15;
		turn = (int)-this->pidTurn->calc(0.70,this->lineMonitor->getAdjustedBrightness(),-100,100);
		// 方向制限
		direction = this->postureEstimation->getDirection() - this->startDirection;
		if(direction < -25 && turn < 0) {
			turn = 0;
		}
		else if(25 < direction && 0 < turn) {
			turn = 0;
		}
	}
	// 足の制御実行
	this->balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
	// しっぽの制御実行
	this->tail->setCommandAngle(angle);

}

/**
 * 制御ステート遷移条件
 * @return	ControlState* 遷移先クラスインスタンス
 * @note	遷移しないときはthisを返す
 */
ControlState* GarageLApproachState::next() {

	// ガレージまでの距離がゼロで遷移
	//Bluetooth::sendMessage(this->balancingWalker->calcGarageDistance());

	// グレーを検知できたときはその位置からガレージまでの残りの距離を再設定して遷移
	if(this->lineMonitor->getGrayFound() == true) {
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
