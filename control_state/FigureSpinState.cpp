/******************************************************************************
 *  FigureSpinState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/24
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  フィギュアLスピン
 *  Author: muraryu
 *****************************************************************************/

#include "FigureSpinState.h"

#include "util/Bluetooth.h"
#include "control_state/FigureDownState.h"

/**
 * コンストラクタ
 */
FigureSpinState::FigureSpinState() {

	Bluetooth::sendMessage("State changed : FigureSpinState\n", 33);

	// メンバ初期化
	this->balancingWalker = BalancingWalker::getInstance();
	this->postureEstimation = PostureEstimation::getInstance();

	// execute(), next()

	// execute(

	// next()

	// その他

	// 初期処理
	startDirection = this->postureEstimation->getDirection();
}

/**
 * デストラクタ
 */
FigureSpinState::~FigureSpinState() {
}

/**
 * 制御ステートに応じた制御を実行
 */
void FigureSpinState::execute() {

	int forward = 0;
	int turn = 50;

	/* 足の制御 */
	// 前進値、旋回値を設定
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
ControlState* FigureSpinState::next() {
	ControlState* baseControlState = base::next();
	if(baseControlState != this) {
		return baseControlState;
	}
	/*
	 * ここまでコード編集禁止
	 * 以下に遷移条件を記述する
	 */

	// 360度回転で遷移
	double diff = this->postureEstimation->getDirection() - this->startDirection;
	Bluetooth::sendMessage(diff);
	if(diff < -350 || 350 < diff) {
		return new FigureDownState();
	}

	return this;
}
