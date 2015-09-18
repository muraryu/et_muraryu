/******************************************************************************
 *  LookupSitDownState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  ルックアップ座り動作
 *  Author: muraryu
 *****************************************************************************/

#include "LookupSitDownState.h"

#include "util/Bluetooth.h"
#include "control_state/LookupPassState.h"
#include "balancer_param.c"

/**
 * コンストラクタ
 */
LookupSitDownState::LookupSitDownState() {

	Bluetooth::sendMessage("State changed : LookupSitDownState\n", 36);

	// シングルトンインスタンス取得
	this->balancingWalker = BalancingWalker::getInstance();
	this->tail = Tail::getInstance();
	this->time = Time::getInstance();

	// 初期処理
	this->balancingWalker->setStandControlMode(false);
	this->startTime = this->time->getTime();

	// 試走会２のパラメータに戻す
	K_THETADOT = 7.5;
	K_F[0] = -1.570303F;
	K_F[1] = -32.2978F;
	K_F[2] = -1.1566F;
	K_F[3] = -2.78873F;

}

/**
 * デストラクタ
 */
LookupSitDownState::~LookupSitDownState() {
}

/**
 * 制御ステートに応じた制御を実行
 */
void LookupSitDownState::execute() {

	int forward = 0;
	int turn = 0;
	int angle = 63;

	/* 足の制御 */
	// 前進値、旋回値を設定
	if(60 < this->tail->getAngle()) {
		forward = 100;
	}
	else {
		forward = 0;
	}
	// 足の制御実行
	balancingWalker->setForwardTurn(forward, turn);

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
ControlState* LookupSitDownState::next() {
	//Bluetooth::sendMessage(this->balancingWalker->calcGarageDistance());
	// 車輪が停止したら遷移
	if(1.0 < this->time->getTime() - this->startTime && this->balancingWalker->getLeftAngularVelocity() <= 0 && this->balancingWalker->getRightAngularVelocity() <= 0) {
		return new LookupPassState();
	}

	return this;
}
