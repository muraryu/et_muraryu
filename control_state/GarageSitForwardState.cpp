/******************************************************************************
 *  GarageSitForwardState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/07/28
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  ガレージ前はしっぽ走行で停止位置まで移動
 *  Author: muraryu
 *****************************************************************************/

#include "GarageSitForwardState.h"

#include "control_state/GarageStopState.h"
#include "util/Bluetooth.h"

/**
 * コンストラクタ
 */
GarageSitForwardState::GarageSitForwardState() {

	Bluetooth::sendMessage("State changed : GarageSitForwardState\n", 39);

	// シングルトンインスタンス取得
	this->balancingWalker = BalancingWalker::getInstance();
	this->tail = Tail::getInstance();
	this->postureEstimation = PostureEstimation::getInstance();

	// インスタンス生成
	this->pidTurn = new PID(3,0,0);

	// 初期処理
	this->balancingWalker->setStandControlMode(false);
	this->startDirection = this->postureEstimation->getDirection();

}

/**
 * デストラクタ
 */
GarageSitForwardState::~GarageSitForwardState() {
	delete this->pidTurn;
}

/**
 * 制御ステートに応じた制御を実行
 */
void GarageSitForwardState::execute() {

	int forward = 20;
	int turn = 0;
	int angle = 85;

	/* 足の制御 */
	// 前進値、旋回値を設定
	turn = (int)this->pidTurn->calc(this->startDirection+5,this->postureEstimation->getDirection(),-30,30); // +5によりガレージ真ん中よりになる（ライン幅の分ずれてるから）
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
ControlState* GarageSitForwardState::next() {

	//Bluetooth::sendMessage(this->balancingWalker->calcGarageDistance());

	// ガレージ停止位置まで前進して遷移
	if(this->balancingWalker->calcGarageDistance() < 0) {
		return new GarageStopState();
	}

	return this;
}
