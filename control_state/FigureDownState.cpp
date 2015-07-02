/******************************************************************************
 *  FigureDownState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/24
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  フィギュアL段差くだり
 *  とりあえず位置制御
 *  Author: muraryu
 *****************************************************************************/

#include "FigureDownState.h"

#include "util/Bluetooth.h"
#include "control_state/TailStandDownState.h"

/**
 * コンストラクタ
 */
FigureDownState::FigureDownState() {

	Bluetooth::sendMessage("State changed : FigureDownState\n", 33);

	// メンバ初期化
	this->balancingWalker = BalancingWalker::getInstance();
	this->lineMonitor = LineMonitor::getInstance();

	// execute(), next()

	// execute()
	this->pid = new PID(240,0,0);

	// next()

	// 初期処理
}

/**
 * デストラクタ
 */
FigureDownState::~FigureDownState() {
}

/**
 * 制御ステートに応じた制御を実行
 */
void FigureDownState::execute() {

	int forward = 20;
	int turn = 0;

	/* 足の制御 */
	// 前進値、旋回値を設定
	turn = (int)-this->pid->calc(this->lineMonitor->getBorderBrightness(),(double)this->lineMonitor->getBrightness(),-100,100);
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
ControlState* FigureDownState::next() {
	ControlState* baseControlState = base::next();
	if(baseControlState != this) {
		return baseControlState;
	}
	/*
	 * ここまでコード編集禁止
	 * 以下に遷移条件を記述する
	 */


	// 経過時間で遷移

	return this;
}
