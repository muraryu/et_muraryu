/******************************************************************************
 *  TailWalkState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  制御ステートに応じた制御を行う
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
	this->balancingWalker = BalancingWalker::getInstance();
	this->time = Time::getInstance();

	// execute(), next()

	// execute()

	// next()
	this->startTime = this->time->getTime();

	// 初期処理
}

/**
 * デストラクタ
 */
TailWalkState::~TailWalkState() {
}

/**
 * 制御ステートに応じた制御を実行
 */
void TailWalkState::execute() {

	int forward = 30;
	int turn = 0;

	/* 足の制御 */
	// 前進値、旋回値を設定
	balancingWalker->setForwardTurn(forward, turn);

}

/**
 * 制御ステート遷移条件
 * @return	ControlState* 遷移先クラスインスタンス
 * @note	遷移しないときはthisを返す
 */
ControlState* TailWalkState::next() {
	ControlState* baseControlState = base::next();
	if(baseControlState != this) {
		return baseControlState;
	}
	/*
	 * ここまでコード編集禁止
	 * 以下に遷移条件を記述する
	 */


	// 経過時刻で遷移
	if(5.0 < this->time->getTime() - this->startTime) {
		return new TailStandUpState();
	}
	return this;

}
