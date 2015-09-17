/******************************************************************************
 *  FigureStopState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/23
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  フィギュアLのぼり後のブレーキ
 *  Author: muraryu
 *****************************************************************************/

#include "FigureStopState.h"

#include "util/Bluetooth.h"
#include "control_state/FigureSpinState.h"

/**
 * コンストラクタ
 */
FigureStopState::FigureStopState() {

	Bluetooth::sendMessage("State changed : FigureStopState\n", 33);

	// シングルトンインスタンス取得
	this->balancingWalker = BalancingWalker::getInstance();
	this->tail = Tail::getInstance();
	this->postureEstimation = PostureEstimation::getInstance();

	// インスタンス生成
	this->pidTurn = new PID(5,0,0);

	// 初期処理
	this->startDirection = this->postureEstimation->getDirection();
}

/**
 * デストラクタ
 */
FigureStopState::~FigureStopState() {
	delete this->pidTurn;
}

/**
 * 制御ステートに応じた制御を実行
 */
void FigureStopState::execute() {

	int forward = 0;
	int turn = 0;
	int angle = 80;

	/* 足の制御 */
	// 前進値、旋回値を設定
	if(77 < this->tail->getAngle()) {
		forward = 100;
	}
	else {
		forward = 0;
	}
	turn = (int)this->pidTurn->calc(this->startDirection,this->postureEstimation->getDirection(),-30,30);
	// 足の制御実行
	balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
	// しっぽの制御実行
	this->tail->setCommandAngle(angle);

	//Bluetooth::sendMessage(this->postureEstimation->getDirection() - this->startDirection);
}

/**
 * 制御ステート遷移条件
 * @return	ControlState* 遷移先クラスインスタンス
 * @note	遷移しないときはthisを返す
 */
ControlState* FigureStopState::next() {

	// 車輪角速度がゼロ以下になったら遷移
	if(this->balancingWalker->getLeftAngularVelocity() <= 0 && this->balancingWalker->getRightAngularVelocity() <= 0) {
		return new FigureSpinState();
	}

	return this;
}
