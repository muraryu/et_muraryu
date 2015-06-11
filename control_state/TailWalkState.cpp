/******************************************************************************
 *  TailWalkState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  制御パターンに応じた制御を行う
 *  ステートパターンConcrete
 *  Author: muraryu
 *****************************************************************************/

#include "TailWalkState.h"

#include "control_state/TailStandUpState.h"
#include "util/Bluetooth.h"

/**
 * コンストラクタ
 */
TailWalkState::TailWalkState() {

	Bluetooth::sendMessage("State changed : TailWalkState\n", 32);

	// メンバ初期化
	// シングルトンではなく、Driverから受け取るか、仲介クラスからとるのもあり
	this->balancingWalker = BalancingWalker::getInstance();
}

/**
 * デストラクタ
 */
TailWalkState::~TailWalkState() {
}

/**
 * 制御パターンに応じた制御を実行
 */
void TailWalkState::execute() {

	int forward = 30;
	int turn = 0;

	/* 足の制御 */
	// 前進値、旋回値を設定
	balancingWalker->setForwardTurn(forward, turn);

}

/**
 * 制御パターン遷移条件
 * @return	ControlState*
 * @note	遷移しないときはthisを返す
 */
ControlState* TailWalkState::next() {
	static int startPos = this->balancingWalker->getRunningDistance();
	if() {
		return new TailStandUpState();
	}
	return this;
}
