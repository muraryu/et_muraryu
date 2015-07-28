/******************************************************************************
 *  GarageLFindState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/23
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  フィギュアL段差のぼり
 *  とりあえず位置制御
 *  Author: muraryu
 *****************************************************************************/

#include "GarageLFindState.h"

#include "util/Bluetooth.h"
#include "control_state/GarageStopState.h"

/**
 * コンストラクタ
 */
GarageLFindState::GarageLFindState() {

	Bluetooth::sendMessage("State changed : GarageLFindState\n", 34);

	// メンバ初期化
	this->balancingWalker = BalancingWalker::getInstance();
	this->tail = Tail::getInstance();
	this->pidTurn = new PID(5,0,0);
	this->postureEstimation = PostureEstimation::getInstance();
	this->lineMonitor = LineMonitor::getInstance();

	// execute(), next()

	// execute()

	// next()

	// その他

	// 初期処理
	this->startDirection = this->postureEstimation->getDirection();
	this->startRightEnc = this->balancingWalker->getRightEnc();
	this->figureEndRightEnc = this->startRightEnc + 36000; // 適当に大きい値で初期化
	this->figureEndFlag = false;
}

/**
 * デストラクタ
 */
GarageLFindState::~GarageLFindState() {
	delete this->pidTurn;
}

/**
 * 制御ステートに応じた制御を実行
 */
void GarageLFindState::execute() {

	int forward = 40;
	int turn = 0;
	int angle = 0;

	/* 足の制御 */
	// 前進値、旋回値を設定
	if(this->figureEndFlag == false) { // フィギュアL段差下りの少し先までは真っ直ぐ進む
		turn = (int)this->pidTurn->calc(this->startDirection,this->postureEstimation->getDirection(),-30,30);
	}
	else { // 段差後すこし進んだらライントレース再開
		this->pidTurn->setPID(80,0,200);
		turn = (int)-this->pidTurn->calc(0.5,this->lineMonitor->getAdjustedBrightness(),-100,100);
	}
	// 足の制御実行
	balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
	if(360 < this->balancingWalker->getRightEnc() - this->figureEndRightEnc) { //
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
ControlState* GarageLFindState::next() {

	// フィギュアL段差下りを検出して位置を記録
	if(this->figureEndFlag == false && 350 < this->balancingWalker->getLeftAngularVelocity() && 350 < this->balancingWalker->getRightAngularVelocity() ) {
		this->figureEndFlag = true;
		this->figureEndRightEnc = this->balancingWalker->getRightEnc();
		this->lineMonitor->changeLineToNormal();
		Bluetooth::sendMessage("Step Found\n");
	}
	else {
		Bluetooth::sendMessage(this->balancingWalker->getLeftAngularVelocity());
	}

	// フィギュアL段差から一定距離進んで遷移
	if(680 < this->balancingWalker->getRightEnc() - this->figureEndRightEnc) {
		return new GarageStopState();
	}

	return this;
}
