/******************************************************************************
 *  CalibrationBlackState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/15
 *  Bluetooth発信合図を待機
 *  ステートパターンConcrete
 *  Author: muraryu
 *****************************************************************************/

#include "CalibrationBlackState.h"

#include "util/Bluetooth.h"
#include "control_state/ReadyState.h"

bool Bluetooth::readyFlag;

/**
 * コンストラクタ
 */
CalibrationBlackState::CalibrationBlackState() {

	Bluetooth::sendMessage("State changed : CalibrationBlackState\n", 39);

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
CalibrationBlackState::~CalibrationBlackState() {
}

/**
 * 制御ステートに応じた制御を実行
 */
void CalibrationBlackState::execute() {

	int forward = 0;
	int turn = 0;
	int angle = 105;

	/* 足の制御 */
	// 前進値、旋回値を設定
	// 足の制御実行
	balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
	// しっぽの制御実行
	this->tail->setCommandAngle(angle);


}

/**
 * 制御ステート遷移条件
 * @return	ControlState* 遷移先クラスインスタンス
 * @note	遷移しないときはthisを返す
 */
ControlState* CalibrationBlackState::next() {
	ControlState* baseControlState = base::next();
	if(baseControlState != this) {
		return baseControlState;
	}
	/*
	 * ここまでコード編集禁止
	 * 以下に遷移条件を記述する
	 */

	if(Bluetooth::readyFlag == true) {
		//return new StopState();
		return new ReadyState();
	}

	return this;
}
