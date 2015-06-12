/******************************************************************************
 *  StopState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  制御パターンに応じた制御を行う
 *  ステートパターンConcrete
 *  Author: muraryu
 *****************************************************************************/

#include "StopState.h"

#include "util/Bluetooth.h"
#include "control_state/TailStandDownState.h"

/**
 * コンストラクタ
 */
StopState::StopState() {

	Bluetooth::sendMessage("State changed : StopState\n", 27);

	// メンバ初期化
	// シングルトンではなく、Driverから受け取るか、仲介クラスからとるのもあり
	this->tail = Tail::getInstance();
	this->time = Time::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();

	this->balancingWalker->setStandControlMode(true);
	this->startTime = this->time->getTime();
}

/**
 * デストラクタ
 */
StopState::~StopState() {
}

/**
 * 制御パターンに応じた制御を実行
 */
void StopState::execute() {

	int forward = 0;
	int turn = 0;
	int angle = 0;

	/* 足の制御 */
	// 旋回値を設定
	// 前進値を設定
	if(10.0 < this->time->getTime() - this->startTime) {
		forward = -50;
	}
	balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
	this->tail->setCommandAngle(angle);


}

/**
 * 制御パターン遷移条件
 * @return	ControlState*
 * @note	遷移しないときはthisを返す
 */
ControlState* StopState::next() {

	// 経過時間で遷移
	if(10.5 < this->time->getTime() - this->startTime) {
		return new TailStandDownState();
	}
	return this;
}
