/******************************************************************************
 *  QuickStartState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  Author: muraryu
 *****************************************************************************/

#include "StartState.h"

#include "util/Bluetooth.h"
#include "control_state/LineTraceState.h"
#include "control_state/Test1State.h"

/**
 * コンストラクタ
 */
StartState::StartState() {

	Bluetooth::sendMessage("State changed : StartState\n", 28);

	// シングルトンインスタンス取得
	this->tail = Tail::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();

	// メンバ初期化
	this->angle = tail->getAngle();
}

/**
 * デストラクタ
 */
StartState::~StartState() {
}

/**
 * 制御ステートに応じた制御を実行
 */
void StartState::execute() {

	int forward = 0;
	int turn = 0;

	/* 足の制御 */
	// 前進値、旋回値を設定
	// 足の制御実行
	this->balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
	/*
	this->angle += 0.05;
	// しっぽの制御実行
	Bluetooth::sendMessage(this->tail->getAngularVelocity());
	if(this->tail->getAngularVelocity() == 0) {
		this->tail->setCommandAngle(this->angle + 20);
	}
	else {
		this->tail->setCommandAngle(this->angle);
	}*/
	this->tail->setCommandAngle(120);
}

/**
 * 制御ステート遷移条件
 * @return	ControlState* 遷移先クラスインスタンス
 * @note	遷移しないときはthisを返す
 */
ControlState* StartState::next() {

	// 前に倒れかけたら遷移
	if(110 < this->tail->getAngle()) {
		this->balancingWalker->init();
		this->balancingWalker->setStandControlMode(true);
		//return new LineTraceState();
		return new Test1State();
	}

	return this;
}
