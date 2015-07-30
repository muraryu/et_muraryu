/******************************************************************************
 *  FigureStandUpState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  Author: muraryu
 *****************************************************************************/

#include "FigureStandUpState.h"

#include "util/Bluetooth.h"
#include "control_state/FigureLineTraceState.h"

/**
 * コンストラクタ
 */
FigureStandUpState::FigureStandUpState() {

	Bluetooth::sendMessage("State changed : FigureStandUpState\n", 36);

	// シングルトンインスタンス取得
	this->tail = Tail::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();

	// メンバ初期化
	this->angle = tail->getAngle();
}

/**
 * デストラクタ
 */
FigureStandUpState::~FigureStandUpState() {
}

/**
 * 制御ステートに応じた制御を実行
 */
void FigureStandUpState::execute() {

	int forward = 0;
	int turn = 0;

	/* 足の制御 */
	// 前進値、旋回値を設定
	// 足の制御実行
	this->balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
	this->angle += 0.30;
	// しっぽの制御実行
	Bluetooth::sendMessage(this->tail->getAngularVelocity());
	if(this->tail->getAngularVelocity() == 0) {
		this->tail->setCommandAngle(this->angle + 20);
	}
	else {
		this->tail->setCommandAngle(this->angle);
	}

}

/**
 * 制御ステート遷移条件
 * @return	ControlState* 遷移先クラスインスタンス
 * @note	遷移しないときはthisを返す
 */
ControlState* FigureStandUpState::next() {

	// 前に倒れかけたら遷移
	if(105 < this->tail->getAngle()) {
		this->balancingWalker->init();
		this->balancingWalker->setStandControlMode(true);
		return new FigureLineTraceState();
	}

	return this;
}
