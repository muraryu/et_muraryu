/******************************************************************************
 *  FigureTailUpState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/07/22
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  しっぽを段差にあげる
 *  Author: muraryu
 *****************************************************************************/

#include "FigureTailUpState.h"

#include "util/Bluetooth.h"
#include "control_state/FigureLineTraceState.h"
//#include "control_state/FigureSpinState.h"

/**
 * コンストラクタ
 */
FigureTailUpState::FigureTailUpState() {

	Bluetooth::sendMessage("State changed : FigureTailUpState\n", 35);

	// シングルトンインスタンス取得
	this->balancingWalker = BalancingWalker::getInstance();
	this->tail = Tail::getInstance();
	this->time = Time::getInstance();

	// 開始時刻取得
	this->startTime = this->time->getTime();

	// 右車輪の目標
	startRightEnc = this->balancingWalker->getRightEnc();

}

/**
 * デストラクタ
 */
FigureTailUpState::~FigureTailUpState() {
}

/**
 * 制御ステートに応じた制御を実行
 */
void FigureTailUpState::execute() {

	int forward = 20;
	int turn = 0;
	int angle = 0;

	double stateTime = this->time->getTime() - this->startTime;

	/* 足の制御 */
	// 前進値、旋回値を設定
	// 足の制御実行
	balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定

	if(0 < stateTime && stateTime <= 0.5) {
		angle = 1000;
		Bluetooth::sendMessage(1);
	}
	else {
		angle = 80;
		Bluetooth::sendMessage(2);
	}
	// しっぽの制御実行
	this->tail->setCommandAngle(angle);
}

/**
 * 制御ステート遷移条件
 * @return	ControlState* 遷移先クラスインスタンス
 * @note	遷移しないときはthisを返す
 */
ControlState* FigureTailUpState::next() {

	// 車輪が一定以上回転したら遷移
	//if(this->balancingWalker->getLeftAngularVelocity() <= 0 && this->balancingWalker->getRightAngularVelocity() <= 0) {
	if(280 < this->balancingWalker->getRightEnc() - this->startRightEnc) {
		//return new FigureSpinState();
		//return new FigureLineTraceState();
	}

	return this;
}
