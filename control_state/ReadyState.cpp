/******************************************************************************
 *  ReadyState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/15
 *  Bluetooth発信合図を待機
 *  ステートパターンConcrete
 *  Author: muraryu
 *****************************************************************************/

#include "ReadyState.h"

#include "util/Bluetooth.h"
#include "control_state/StopState.h"
//#include "control_state/LineTraceState.h"

bool Bluetooth::readyFlag;

/**
 * コンストラクタ
 */
ReadyState::ReadyState() {

	Bluetooth::sendMessage("State changed : ReadyState\n", 28);

	// メンバ初期化
	this->tail = Tail::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();

	// execute(), next()

	// execute()

	// next()

	// 初期処理
	this->balancingWalker->setStandControlMode(false);
}

/**
 * デストラクタ
 */
ReadyState::~ReadyState() {
}

/**
 * 制御ステートに応じた制御を実行
 */
void ReadyState::execute() {

	int forward = 0;
	int turn = 0;
	int angle = 105;

	/* 足の制御 */
	// 旋回値を設定
	// 前進値を設定
	balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
	this->tail->setCommandAngle(angle);


}

/**
 * 制御ステート遷移条件
 * @return	ControlState* 遷移先クラスインスタンス
 * @note	遷移しないときはthisを返す
 */
ControlState* ReadyState::next() {
	ControlState* baseControlState = base::next();
	if(baseControlState != this) {
		return baseControlState;
	}
	/*
	 * ここまでコード編集禁止
	 * 以下に遷移条件を記述する
	 */

	if(Bluetooth::readyFlag == true) {
		return new StopState();
		//return new LineTraceState();
	}

	return this;
}
