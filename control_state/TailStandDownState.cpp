/******************************************************************************
 *  TailStandDownState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  Author: muraryu
 *****************************************************************************/

#include "TailStandDownState.h"

#include "util/Bluetooth.h"
#include "control_state/TailWalkState.h"

/**
 * コンストラクタ
 */
TailStandDownState::TailStandDownState() {

	Bluetooth::sendMessage("State changed : TailStandDownState\n", 36);

	// メンバ初期化
	this->tail = Tail::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();
	this->time = Time::getInstance();

	// execute(), next()

	// execute()
	this->commandAngle1 = 100;
	this->flag1 = false;
	this->startTime1 = this->time->getTime();
	this->satValue1 = 0;

	// next()
	this->startTime2 = this->time->getTime();
	this->satValue2 = 0;

	// 初期処理
	this->balancingWalker->setStandControlMode(false);
}

/**
 * デストラクタ
 */
TailStandDownState::~TailStandDownState() {
}

/**
 * 制御ステートに応じた制御を実行
 */
void TailStandDownState::execute() {

	int forward = 0;
	int turn = 0;

	/* 足の制御 */
	// 前進値、旋回値を設定
	balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
	if(this->flag1 == false) {
		// しっぽを下ろして2秒間安定したか
		if(this->satValue1 == this->tail->getAngle() && 2.0 < this->time->getTime() - this->startTime1) {
			this->flag1 = true;
		}
		else {
			this->satValue1 = this->tail->getAngle();
			this->startTime1 = this->time->getTime();
		}
	}
	else {
		// 74degまで15deg/secの速さでしっぽを上げて機体を傾ける
		this->commandAngle1 -= 0.06;
		if(this->commandAngle1 < 74) {
			this->commandAngle1 = 74;
		}
	}

	this->tail->setCommandAngle((int)(this->commandAngle1));

}

/**
 * 制御ステート遷移条件
 * @return	ControlState* 遷移先クラスインスタンス
 * @note	遷移しないときはthisを返す
 */
ControlState* TailStandDownState::next() {
	ControlState* baseControlState = base::next();
	if(baseControlState != this) {
		return baseControlState;
	}
	/*
	 * ここまでコード編集禁止
	 * 以下に遷移条件を記述する
	 */


	int angle = this->tail->getAngle();

	// しっぽ停止時間計算
	if(this->satValue2 != angle) {
		this->startTime2 = this->time->getTime();
		this->satValue2 = angle;
	}

	// しっぽが3秒間停止したら遷移
	if(3.0 < this->time->getTime() - this->startTime2) {
		return new TailWalkState();
	}

	return this;
}
