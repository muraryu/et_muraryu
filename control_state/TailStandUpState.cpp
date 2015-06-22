/******************************************************************************
 *  TailStandUpState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/12
 *  制御ステートに応じた制御を行う
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
	this->tail = Tail::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();

	// execute(), next()

	// execute()

	// next()

	// 初期処理
}

/**
 * デストラクタ
 */
TailStandUpState::~TailStandUpState() {
}

/**
 * 制御ステートに応じた制御を実行
 */
void TailStandUpState::execute() {

	int forward = 0;
	int turn = 0;
	double angle = 110;

	/* 足の制御 */
	// 前進値、旋回値を設定
	// 足の制御実行
	balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
	// しっぽの制御実行
	this->tail->setCommandAngle((int)angle);

}

/**
 * 制御ステート遷移条件
 * @return	ControlState* 遷移先クラスインスタンス
 * @note	遷移しないときはthisを返す
 */
ControlState* TailStandUpState::next() {
	ControlState* baseControlState = base::next();
	if(baseControlState != this) {
		return baseControlState;
	}
	/*
	 * ここまでコード編集禁止
	 * 以下に遷移条件を記述する
	 */


	// 前に倒れかけたら遷移
	if(110 < this->tail->getAngle()) {
		this->balancingWalker->init();
		return new StopState();
	}
	return this;
}
