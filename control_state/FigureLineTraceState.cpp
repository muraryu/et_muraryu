/******************************************************************************
 *  FigureLineTraceState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/07/01
 *  ステートパターンConcrete
 *  フィギュアLに上ったあと停止位置までラインに追従する
 *  Author: muraryu
 *****************************************************************************/

#include "FigureLineTraceState.h"

#include "util/Bluetooth.h"
#include "control_state/FigureSpinState.h"

/**
 * コンストラクタ
 */
FigureLineTraceState::FigureLineTraceState() {

	Bluetooth::sendMessage("State changed : FigureLineTraceState\n", 38);

	/* メンバ初期化 */
	// シングルトン取得
	this->balancingWalker = BalancingWalker::getInstance();
	this->lineMonitor = LineMonitor::getInstance();

	// execute(), next()
	this->startRightEnc = this->balancingWalker->getRightEnc();

	// execute()
	this->pid = new PID(240,0,0);

	// next()

	/* 初期処理 */

}

/**
 * デストラクタ
 */
FigureLineTraceState::~FigureLineTraceState() {
	delete this->pid;
}

/**
 * 制御ステートに応じた制御を実行
 */
void FigureLineTraceState::execute() {

	int forward = 20;
	int turn = 0;
	int angle = 0;

	/* 足の制御 */
	// 前進値、旋回値を設定
	turn = -this->pid->calc(this->lineMonitor->getBorderBrightness(),(double)this->lineMonitor->getBrightness(),-100,100);
	// 足の制御実行
	balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
	// しっぽの制御実行

}

/**
 * 制御ステート遷移条件
 * @return	ControlState* 遷移先クラスインスタンス
 * @note	遷移しないときはthisを返す
 */
ControlState* FigureLineTraceState::next() {
	ControlState* baseControlState = base::next();
	if(baseControlState != this) {
		return baseControlState;
	}
	/*
	 * ここまでコード編集禁止
	 * 以下に遷移条件を記述する
	 */

	// スピン位置まで一定量進んで遷移
	if(270 < this->balancingWalker->getRightEnc() - this->startRightEnc) {
		return new FigureSpinState();
	}

	return this;
}
