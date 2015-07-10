/******************************************************************************
 *  FigureStopState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/23
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  フィギュアL段差のぼり
 *  とりあえず位置制御
 *  Author: muraryu
 *****************************************************************************/

#include "FigureStopState.h"

#include "util/Bluetooth.h"
#include "control_state/FigureLineTraceState.h"
//#include "control_state/FigureSpinState.h"

/**
 * コンストラクタ
 */
FigureStopState::FigureStopState() {

	Bluetooth::sendMessage("State changed : FigureStopState\n", 33);

	// メンバ初期化
	this->balancingWalker = BalancingWalker::getInstance();
	this->pid = new PID(0.1,0.0001,0);

	// execute(), next()

	// execute()

	// next()

	// その他

	// 初期処理
	this->referenceRightEnc = this->balancingWalker->getRightEnc() + 360;
}

/**
 * デストラクタ
 */
FigureStopState::~FigureStopState() {
}

/**
 * 制御ステートに応じた制御を実行
 */
void FigureStopState::execute() {

	int forward = 0;
	int turn = 0;

	/* 足の制御 */
	// 前進値、旋回値を設定
	forward = this->pid->calc(this->referenceRightEnc, this->balancingWalker->getRightEnc(), -100, 100);
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
ControlState* FigureStopState::next() {
	ControlState* baseControlState = base::next();
	if(baseControlState != this) {
		return baseControlState;
	}
	/*
	 * ここまでコード編集禁止
	 * 以下に遷移条件を記述する
	 */


	// 車輪が一定以上回転したら遷移
	//if(this->balancingWalker->getLeftAngularVelocity() <= 0 && this->balancingWalker->getRightAngularVelocity() <= 0) {
	if(this->referenceRightEnc - this->balancingWalker->getRightEnc() < 180) {
		//return new FigureSpinState();
		return new FigureLineTraceState();
	}

	return this;
}
