/******************************************************************************
 *  GarageRecoveryState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/09/15
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  ガレージ入れ直し動作
 *  Author: muraryu
 *****************************************************************************/

#include "GarageRecoveryState.h"

#include "control_state/GarageStopState.h"
#include "util/Bluetooth.h"

/**
 * コンストラクタ
 */
GarageRecoveryState::GarageRecoveryState() {

	Bluetooth::sendMessage("State changed : GarageRecoveryState\n", 37);

	// メンバ初期化
	this->balancingWalker = BalancingWalker::getInstance();
	this->tail = Tail::getInstance();
	this->postureEstimation = PostureEstimation::getInstance();
	this->pidTurn = new PID(3,0,0);
	this->time = Time::getInstance();

	// 初期処理
	this->balancingWalker->setStandControlMode(false);
	this->forward = 40;
	this->startDirection = this->postureEstimation->getDirection();
	this->startTime = this->time->getTime();
	this->startRightEnc = this->balancingWalker->getRightEnc();
	this->garageEndRightEnc = this->balancingWalker->getRightEnc();
	this->turnFlag1 = false;
	this->turnFlag2 = false;
	this->endFlag = false;

}

/**
 * デストラクタ
 */
GarageRecoveryState::~GarageRecoveryState() {
	delete this->pidTurn;
}

/**
 * 制御ステートに応じた制御を実行
 */
void GarageRecoveryState::execute() {

	int turn = 0;
	int angle = 85;

	/* 足の制御 */
	// 前進値、旋回値を設定
	if(this->turnFlag1 == false && this->turnFlag2 == false && (80 < this->balancingWalker->getRightEnc() - this->startRightEnc || 2.0 < this->time->getTime() - this->startTime)) { // 遷移時の位置から5cm前進or2.0秒経過で後退 15.882deg = 1cm
		this->turnFlag1 = true;
		this->forward = -30;
		this->garageEndRightEnc = this->balancingWalker->getRightEnc();
	} else if(this->turnFlag1 == true && this->turnFlag2 == false && this->balancingWalker->getRightEnc() - this->garageEndRightEnc < -397) { // 後退終了位置に来たら再び前進 25cm後退
		this->turnFlag2 = true;
		this->forward = 20;
	} else if(this->turnFlag1 == true && this->turnFlag2 == true && -15 < this->balancingWalker->getRightEnc() - this->garageEndRightEnc) { // 終了位置で停止 24cm前進
		this->endFlag = true;
		this->forward = 0;
	}
	turn = (int)this->pidTurn->calc(this->startDirection,this->postureEstimation->getDirection(),-30,30); // +5によりガレージ真ん中よりになる（ライン幅の分ずれてるから）
	// 足の制御実行
	this->balancingWalker->setForwardTurn(this->forward, turn);

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
ControlState* GarageRecoveryState::next() {

	// ガレージ停止位置まで前進して遷移
	if(this->endFlag == true) {
		return new GarageStopState();
	}

	return this;
}
