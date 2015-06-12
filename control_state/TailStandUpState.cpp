/******************************************************************************
 *  TailStandUpState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/12
 *  制御パターンに応じた制御を行う
 *  ステートパターンConcrete
 *  Author: muraryu
 *****************************************************************************/

#include "TailStandUpState.h"

#include "util/Bluetooth.h"
#include "control_state/StopState.h"

/**
 * コンストラクタ
 */
TailStandUpState::TailStandUpState() {

	Bluetooth::sendMessage("State changed : TailStandUpState\n", 34);

	// メンバ初期化
	// シングルトンではなく、Driverから受け取るか、仲介クラスからとるのもあり
	this->tail = Tail::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();
}

/**
 * デストラクタ
 */
TailStandUpState::~TailStandUpState() {
}

/**
 * 制御パターンに応じた制御を実行
 */
void TailStandUpState::execute() {

	int forward = 0;
	int turn = 0;
	double angle = 100;

	/* 足の制御 */
	// 前進値、旋回値を設定
	balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
	this->tail->setCommandAngle((int)angle);

}

/**
 * 制御パターン遷移条件
 * @return	ControlState*
 * @note	遷移しないときはthisを返す
 */
ControlState* TailStandUpState::next() {

	// 前に倒れかけたら遷移
	if(100 < this->tail->getAngle()) {
		this->balancingWalker->init();
		return new StopState();
	}
	return this;
}
