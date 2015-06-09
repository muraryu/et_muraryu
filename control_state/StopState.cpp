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
	this->tail = Tail::getInstance();
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

	/* 足の制御 */
	// 旋回値を設定


	// 前進値を設定


	/* しっぽの制御 */
	// 角度目標値を設定
	tail->setAngle(0);


}

/**
 * 制御パターン遷移条件
 */
ControlState* StopState::next() {

	return this;
}
