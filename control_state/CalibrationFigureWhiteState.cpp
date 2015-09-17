/******************************************************************************
 *  CalibrationFigureWhiteState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/07/02
 *  ステートパターンConcrete
 *  タッチボタンを押すとフィギュアLの白の値をキャリブレーションする
 *  Author: muraryu
 *****************************************************************************/

#include "CalibrationFigureWhiteState.h"

#include "util/Bluetooth.h"
#include "control_state/ReadyState.h"

/**
 * コンストラクタ
 */
CalibrationFigureWhiteState::CalibrationFigureWhiteState() {

	Bluetooth::sendMessage("State changed : CalibrationFigureWhiteState\n", 45);

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
CalibrationFigureWhiteState::~CalibrationFigureWhiteState() {
}

/**
 * 制御ステートに応じた制御を実行
 */
void CalibrationFigureWhiteState::execute() {

	int angle = 45;

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
ControlState* CalibrationFigureWhiteState::next() {
	ControlState* baseControlState = base::next();
	if(baseControlState != this) {
		return baseControlState;
	}
	/*
	 * ここまでコード編集禁止
	 * 以下に遷移条件を記述する
	 */

	// タッチボタンが押されたら遷移
	if(this->uiManager->isButtonPressed() == true) {
		// 現在の輝度をフィギュアLの白の値とする
		this->lineMonitor->calibrateFigureWhite();
		return new ReadyState();
	}

	return this;
}
