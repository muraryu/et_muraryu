/******************************************************************************
 *  StopState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  制御パターンに応じた制御を行う
 *  ステートパターンConcrete
 *  Author: muraryu
 *****************************************************************************/

#include "StopState.h"

#include "util/Bluetooth.h"

/**
 * コンストラクタ
 */
StopState::StopState() {

	Bluetooth::sendMessage("State changed : StopState\n", 27);

	// メンバ初期化
	// シングルトンではなく、Driverから受け取るか、仲介クラスからとるのもあり
	this->tail = Tail::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();
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

	return this;
}
