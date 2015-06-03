/******************************************************************************
 *  StopState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  制御パターンに応じた制御を行う
 *  ステートパターンConcrete
 *  Author: muraryu
 *****************************************************************************/

#include "StopState.h"

/**
 * コンストラクタ
 */
StopState::StopState() {
}

/**
 * デストラクタ
 */
StopState::~StopState() {
}

/**
 * 仮想関数のオーバーライド
 */
ControlState* StopState::execute() {

	// 制御


	// 制御パターン遷移条件
	return this;
}
