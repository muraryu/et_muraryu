/******************************************************************************
 *  TailStandState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  制御パターンに応じた制御を行う
 *  ステートパターンConcrete
 *  Author: muraryu
 *****************************************************************************/

#include "TailStandState.h"

#include "util/Bluetooth.h"

/**
 * コンストラクタ
 */
TailStandState::TailStandState() {

	Bluetooth::sendMessage("State changed : TailStandState\n", 32);

	// メンバ初期化
	// シングルトンではなく、Driverから受け取るか、仲介クラスからとるのもあり
	this->tail = Tail::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();
}

/**
 * デストラクタ
 */
TailStandState::~TailStandState() {
}

/**
 * 制御パターンに応じた制御を実行
 */
void TailStandState::execute() {

	int forward = 0;
	int turn = 0;
	int angle = 30;

	/* 足の制御 */
	// 前進値、旋回値を設定
	balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
	this->tail->setCommandAngle(angle);

}

/**
 * 制御パターン遷移条件
 */
ControlState* TailStandState::next() {

	return this;
}
