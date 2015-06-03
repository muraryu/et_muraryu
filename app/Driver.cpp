/******************************************************************************
 *  Driver.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  制御パターンに応じた制御を行う
 *  ステートパターンContext
 *  Author: muraryu
 *****************************************************************************/

extern "C" {
#include "ecrobot_interface.h"
}
#include "Driver.h"

/**
 * コンストラクタ
 * Driverパラメータ、偏差積分値、初回入力値を初期化
 */
Driver::Driver(ControlState* controlState) {
	this->controlState = controlState;
	this->prevControlState = controlState;
}

/**
 * デストラクタ
 */
Driver::~Driver() {
}

/**
 * 制御パターンに応じた制御を行う
 * @param r 目標値
 * @param u 制御量
 */
void Driver::execute() {

	// 制御を実行し、次の制御パターンを受け取る
	this->controlState = this->controlState->execute();

	// 制御パターンが遷移したとき、遷移前のインスタンスを破棄
	if(this->prevControlState != this->controlState) {
		delete this->prevControlState;
		this->prevControlState = this->controlState;
	}
}

void Driver::setControlState(ControlState* controlState) {
	this->controlState = controlState;
}
