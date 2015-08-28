/******************************************************************************
 *  CalibrationWhiteState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/15
 *  Bluetooth発信合図を待機
 *  ステートパターンConcrete
 *  Author: muraryu
 *****************************************************************************/

#include "CalibrationWhiteState.h"

#include "util/Bluetooth.h"
#include "control_state/CalibrationBlackState.h"

/**
 * コンストラクタ
 */
CalibrationWhiteState::CalibrationWhiteState() {

	Bluetooth::sendMessage("State changed : CalibrationWhiteState\n", 39);

	// メンバ初期化
	this->tail = Tail::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();
	this->uiManager = UIManager::getInstance();
	this->lineMonitor = LineMonitor::getInstance();

	// execute(), next()

	// execute()

	// next()

	// 初期処理
	this->balancingWalker->setStandControlMode(false);
	this->uiManager->resetButtonPressed();
}

/**
 * デストラクタ
 */
CalibrationWhiteState::~CalibrationWhiteState() {
}

/**
 * 制御ステートに応じた制御を実行
 */
void CalibrationWhiteState::execute() {

	int forward = 0;
	int turn = 0;
	int angle = 45;

	/* 足の制御 */
	// 前進値、旋回値を設定
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
ControlState* CalibrationWhiteState::next() {

	// タッチボタンが押されたら遷移
	if(this->uiManager->isButtonPressed() == true) {
		// 現在の輝度を白の値とする
		this->lineMonitor->calibrateWhite();
		return new CalibrationBlackState();
	}

	return this;
}
