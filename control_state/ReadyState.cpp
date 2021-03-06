/******************************************************************************
 *  ReadyState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/15
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  Bluetooth発信合図を待機
 *  Author: muraryu
 *****************************************************************************/

#include "ReadyState.h"

#include "util/Bluetooth.h"
#include "control_state/Test1State.h"
#include "control_state/Test2State.h"
#include "control_state/FigureLineTraceState.h"
#include "control_state/FigureSpinState.h"
#include "control_state/LookupFindState.h"
#include "control_State/StartState.h"
#include "control_state/LineTraceState.h"
#include "control_state/FigureStandUpState.h"
#include "control_state/GarageSitForwardState.h"
#include "control_state/GarageStopState.h"

/**
 * コンストラクタ
 */
ReadyState::ReadyState() {

	Bluetooth::sendMessage("State changed : ReadyState\n", 28);

	// シングルトンインスタンス取得
	this->tail = Tail::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();
	this->uiManager = UIManager::getInstance();

	// 初期処理
	this->uiManager->resetReadyToStart();
}

/**
 * デストラクタ
 */
ReadyState::~ReadyState() {
}

/**
 * 制御ステートに応じた制御を実行
 */
void ReadyState::execute() {

	int forward = 0;
	int turn = 0;
	int angle = 105;

	/* 足の制御 */
	// 前進値、旋回値を設定
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
ControlState* ReadyState::next() {

	// 走行開始合図が来たら遷移
	if(this->uiManager->isReadyToStart() == true) {
		this->balancingWalker->init();
		this->balancingWalker->setStandControlMode(true);
		return new LineTraceState(); //TODO 当日本番
		//return new Test1State();
		//return new Test2State();
		//return new QuickStartState();
		//return new FigureStandUpState(); //TODO 当日調整用 コースR
		//return new LookupFindState(); //TODO 当日調整用 コースL
		//return new GarageSitForwardState();
		//return new GarageStopState();
	}

	return this;
}
