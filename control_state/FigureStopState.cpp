/******************************************************************************
 *  FigureStopState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/23
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  フィギュアL段差のぼり
 *  とりあえず位置制御
 *  Author: muraryu
 *****************************************************************************/

#include "FigureStopState.h"

#include "util/Bluetooth.h"
#include "control_state/FigureLineTraceState.h"
#include "control_state/FigureSpinState.h"

/**
 * コンストラクタ
 */
FigureStopState::FigureStopState() {

	Bluetooth::sendMessage("State changed : FigureStopState\n", 33);

	// メンバ初期化
	this->balancingWalker = BalancingWalker::getInstance();
	this->tail = Tail::getInstance();
	this->pidForward = new PID(0.13,0.0001,0);
	this->pidTurn = new PID(5,0,0);
	this->postureEstimation = PostureEstimation::getInstance();
	this->lineMonitor = LineMonitor::getInstance();

	// execute(), next()

	// execute()
	this->angle = 80;

	// next()

	// その他

	// 初期処理
	this->referenceRightEnc = this->balancingWalker->getRightEnc() + 450;
	this->startDirection = this->postureEstimation->getDirection();
}

/**
 * デストラクタ
 */
FigureStopState::~FigureStopState() {
	delete this->pidForward;
	delete this->pidTurn;
}

/**
 * 制御ステートに応じた制御を実行
 */
void FigureStopState::execute() {

	int forward = 0;
	int turn = 0;

	/* 足の制御 */
	// 前進値、旋回値を設定
	//forward = this->pidForward->calc((double)this->referenceRightEnc, (double)this->balancingWalker->getRightEnc(), -100, 100);
	//turn = this->pidTurn->calc(this->startDirection,this->postureEstimation->getDirection(),-30,30);
	// 足の制御実行
	balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
	/*
	if(this->balancingWalker->getLeftAngularVelocity() <= 10 && this->balancingWalker->getRightAngularVelocity() <= 10) {
		this->angle += 0.1;
		if(90 < this->angle) {
			this->angle = 90;
		}
	}
	*/
	// しっぽの制御実行
	this->tail->setCommandAngle(angle);

	//Bluetooth::sendMessage(this->lineMonitor->getBrightness()*100);
	Bluetooth::sendMessage(this->postureEstimation->getDirection() - this->startDirection);
}

/**
 * 制御ステート遷移条件
 * @return	ControlState* 遷移先クラスインスタンス
 * @note	遷移しないときはthisを返す
 */
ControlState* FigureStopState::next() {

	// 車輪角速度がゼロ以下、かつ、しっぽが100°前後になったら
	if(this->balancingWalker->getLeftAngularVelocity() <= 0 && this->balancingWalker->getRightAngularVelocity() <= 0) {// && 88 < this->tail->getAngle()) {
	//if(this->referenceRightEnc - this->balancingWalker->getRightEnc() < 180) {
		//return new FigureSpinState();
		//return new FigureLineTraceState();
	}

	return this;
}
