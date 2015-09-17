/******************************************************************************
 *  CalibrationBlackState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/15
 *  ステートパターンConcrete
 *  キャリブレーション黒
 *  Author: muraryu
 *****************************************************************************/

#include "CalibrationBlackState.h"

#include "util/Bluetooth.h"
#include "control_state/CalibrationFigureWhiteState.h"

/**
 * コンストラクタ
 */
CalibrationBlackState::CalibrationBlackState() {

	Bluetooth::sendMessage("State changed : CalibrationBlackState\n", 39);

	// シングルトンインスタンス取得
	this->uiManager = UIManager::getInstance();
	this->lineMonitor = LineMonitor::getInstance();
	this->tail = Tail::getInstance();

	// 初期処理
	this->uiManager->resetButtonPressed();
}

/**
 * デストラクタ
 */
CalibrationBlackState::~CalibrationBlackState() {
}

/**
 * 制御ステートに応じた制御を実行
 */
void CalibrationBlackState::execute() {

	int angle = 105;

	/* 足の制御 */
	// 前進値、旋回値を設定
	// 足の制御実行

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
ControlState* CalibrationBlackState::next() {

	// タッチボタンが押されたら遷移
	if(this->uiManager->isButtonPressed() == true) {
		// 現在の輝度を黒の値とする
		this->lineMonitor->calibrateBlack();
		return new CalibrationFigureWhiteState();
	}

	return this;
}
