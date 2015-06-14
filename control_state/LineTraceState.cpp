/******************************************************************************
 *  LineTraceState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/05
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  Author: muraryu
 *****************************************************************************/

#include "LineTraceState.h"

#include "util/Bluetooth.h"

/**
 * コンストラクタ
 */
LineTraceState::LineTraceState() {

	Bluetooth::sendMessage("State changed : LineTraceState\n", 32);

	/* メンバ初期化 */
	// シングルトン取得
	this->tail = Tail::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();

	// execute(), next()

	// execute()

	// next()

	/* 初期処理 */
	this->balancingWalker->setStandControlMode(true);

}

/**
 * デストラクタ
 */
LineTraceState::~LineTraceState() {
}

/**
 * 制御ステートに応じた制御を実行
 */
void LineTraceState::execute() {

	int forward = 20;
	int turn = 0;
	int angle = 0;

	/* 足の制御 */
	// 旋回値を設定
	// ライントレースモードがオンなので設定しない
	// 前進値を設定
	balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
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



	return this;
}
