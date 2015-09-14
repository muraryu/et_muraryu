/******************************************************************************
 *  LookupPassState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  ルックアップしっぽ走行の往復動作
 *  Author: muraryu
 *****************************************************************************/

#include "LookupPassState.h"

#include "control_state/LookupStandUpState.h"
#include "util/Bluetooth.h"

/**
 * コンストラクタ
 */
LookupPassState::LookupPassState() {

	Bluetooth::sendMessage("State changed : LookupPassState\n", 33);

	// シングルトンインスタンス取得
	this->balancingWalker = BalancingWalker::getInstance();
	this->time = Time::getInstance();
	this->postureEstimation = PostureEstimation::getInstance();

	// メンバ初期化
	this->startTime = this->time->getTime();
	this->startRightEnc = this->balancingWalker->getRightEnc();
	this->startDirection = this->postureEstimation->getDirection();
	this->pidTurn = new PID(3,0,0);
	this->backFlag = false;
	this->forwardAgainFlag = false;
	this->forward = 30;

	// 初期処理
}

/**
 * デストラクタ
 */
LookupPassState::~LookupPassState() {
	delete this->pidTurn;
}

/**
 * 制御ステートに応じた制御を実行
 */
void LookupPassState::execute() {

	int turn = 0;

	/* 足の制御 */
	// 前進値、旋回値を設定
	if(this->forwardAgainFlag == false && this->backFlag == false && 550 < this->balancingWalker->getRightEnc() - this->startRightEnc) { // 1回目前進量
		this->backFlag = true;
		this->forward = 0;
	}
	else if(this->forwardAgainFlag == false && this->backFlag == true && 60 < this->balancingWalker->getRightEnc() - this->startRightEnc) { // 後退量
		this->forward -= 0.06;
		if(this->forward < -30) {
			this->forward = -30;
		}
	}
	else if(this->forwardAgainFlag == false && this->backFlag == true && this->balancingWalker->getRightEnc() - this->startRightEnc < 60) { // 後退量
		this->forwardAgainFlag = true;
		this->forward = 30;
	}
	turn = (int)this->pidTurn->calc(this->startDirection,this->postureEstimation->getDirection(),-30,30);
	// 足の制御実行
	this->balancingWalker->setForwardTurn(this->forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
	// しっぽの制御実行

}

/**
 * 制御ステート遷移条件
 * @return	ControlState* 遷移先クラスインスタンス
 * @note	遷移しないときはthisを返す
 */
ControlState* LookupPassState::next() {
	//Bluetooth::sendMessage(this->balancingWalker->calcGarageDistance());
	// タイヤが一定以上回転したら
	if(600 < this->balancingWalker->getRightEnc() - this->startRightEnc) {
		return new LookupStandUpState();
	}
	return this;

}
