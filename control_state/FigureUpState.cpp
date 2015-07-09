/******************************************************************************
 *  FigureUpState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/23
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  フィギュアL段差のぼり
 *  とりあえず位置制御
 *  Author: muraryu
 *****************************************************************************/

#include "FigureUpState.h"

#include "util/Bluetooth.h"
#include "control_state/FigureLineTraceState.h"

/**
 * コンストラクタ
 */
FigureUpState::FigureUpState() {

	Bluetooth::sendMessage("State changed : FigureUpState\n", 31);

	// メンバ初期化
	this->balancingWalker = BalancingWalker::getInstance();

	// execute(), next()

	// execute()

	// next()

	// その他
	this->pid = new PID(0.06,0,0);

	// 初期処理
	this->startRightEnc = this->balancingWalker->getRightEnc();
}

/**
 * デストラクタ
 */
FigureUpState::~FigureUpState() {
	delete this->pid;
}

/**
 * 制御ステートに応じた制御を実行
 */
void FigureUpState::execute() {

	int forward = 50;
	int turn = 0;

	/* 足の制御 */
	// 前進値、旋回値を設定
	//turn
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
ControlState* FigureUpState::next() {
	ControlState* baseControlState = base::next();
	if(baseControlState != this) {
		return baseControlState;
	}
	/*
	 * ここまでコード編集禁止
	 * 以下に遷移条件を記述する
	 */


	// 車輪が一定以上回転したら遷移
	if(360 < this->balancingWalker->getRightEnc() - this->startRightEnc) {
		return new FigureLineTraceState();
	}

	return this;
}
