/******************************************************************************
 *  GarageSitDownState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  ガレージ前しっぽ座り動作
 *  Author: muraryu
 *****************************************************************************/

#include "GarageSitDownState.h"

#include "util/Bluetooth.h"
#include "control_state/GarageSitForwardState.h"

/**
 * コンストラクタ
 */
GarageSitDownState::GarageSitDownState() {

	//Bluetooth::sendMessage("State changed : GarageSitDownState\n", 36);

	// シングルトンインスタンス取得
	this->tail = Tail::getInstance();
	this->time = Time::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();
	this->lineMonitor = LineMonitor::getInstance();

	// 初期処理
	this->startTime = this->time->getTime();
	this->referenceEncValue = this->balancingWalker->getRightEnc();
	this->balancingWalker->setStandControlMode(false);
}

/**
 * デストラクタ
 */
GarageSitDownState::~GarageSitDownState() {
}

/**
 * 制御ステートに応じた制御を実行
 */
void GarageSitDownState::execute() {

	int forward = 0;
	int turn = 0;
	int angle = 85;

	/* 足の制御 */
	// 前進値、旋回値を設定
	if(82 < this->tail->getAngle()) {
		forward = 80;
	}
	else {
		forward = 0;
	}
	// 足の制御実行
	this->balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
	// しっぽの制御実行
	this->tail->setCommandAngle(angle);

}

/**
 * 制御ステート遷移条件
 * @return	ControlState* 遷移先クラスインスタンス
 * @note	遷移しないときはthisを返す
 */
ControlState* GarageSitDownState::next() {

	//Bluetooth::sendMessage(this->balancingWalker->calcGarageDistance());

	// 少し時間が経過した後車輪が止まったら遷移
	if(0.2 < this->time->getTime() - this->startTime && this->balancingWalker->getRightAngularVelocity() <= 50) {
		//return new FigureUpState();
		return new GarageSitForwardState();
	}

	return this;
}
