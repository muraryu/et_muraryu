/******************************************************************************
 *  LineTraceState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/05
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  Author: muraryu
 *****************************************************************************/

#include "LineTraceState.h"

#include "util/Bluetooth.h"
#include "control_state/FigureFindState.h"
#include "control_state/CalibrationWhiteState.h"

/**
 * コンストラクタ
 */
LineTraceState::LineTraceState() {

	Bluetooth::sendMessage("State changed : LineTraceState\n", 32);

	/* メンバ初期化 */
	// シングルトン取得
	this->tail = Tail::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();
	this->lineMonitor = LineMonitor::getInstance();

	// execute(), next()

	// execute()
	this->pid = new PID(200,0,0);

	// next()

	/* 初期処理 */
	this->balancingWalker->setStandControlMode(true);

}

/**
 * デストラクタ
 */
LineTraceState::~LineTraceState() {
	delete this->pid;
}

/**
 * 制御ステートに応じた制御を実行
 */
void LineTraceState::execute() {

	int forward = 30;
	int turn = 0;
	int angle = 0;

	/* 足の制御 */
	// 前進値、旋回値を設定
	turn = (int)-this->pid->calc(this->lineMonitor->getBorderBrightness(),this->lineMonitor->getBrightness(),-100,100);
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
ControlState* LineTraceState::next() {
	ControlState* baseControlState = base::next();
	if(baseControlState != this) {
		return baseControlState;
	}
	/*
	 * ここまでコード編集禁止
	 * 以下に遷移条件を記述する
	 */

	if(13000 < this->balancingWalker->getRightEnc()) {
		return new CalibrationWhiteState();
	}


	return this;
}
