/******************************************************************************
 *  LookupSitDownState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  Author: muraryu
 *****************************************************************************/

#include "LookupSitDownState.h"

#include "util/Bluetooth.h"
#include "control_state/LookupPassState.h"

/**
 * コンストラクタ
 */
LookupSitDownState::LookupSitDownState() {

	Bluetooth::sendMessage("State changed : LookupSitDownState\n", 36);

	// メンバ初期化
	this->balancingWalker = BalancingWalker::getInstance();
	this->tail = Tail::getInstance();

	// execute(), next()

	// execute()

	// next()

	// その他

	// 初期処理
	this->balancingWalker->setStandControlMode(false);
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
	int angle = 75;

	/* 足の制御 */
	// 前進値、旋回値を設定
	Bluetooth::sendMessage(this->tail->getAngle());
	if(72 < this->tail->getAngle()) {
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

	// しっぽ角度が78°以下でが5秒間停止したら遷移 TODO
	if(this->balancingWalker->getLeftAngularVelocity() <= 0 && this->balancingWalker->getRightAngularVelocity() <= 0) {
		return new LookupPassState();
	}

	return this;
}
