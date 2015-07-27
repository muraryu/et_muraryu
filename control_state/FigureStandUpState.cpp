/******************************************************************************
 *  FigureStandUpState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  Author: muraryu
 *****************************************************************************/

#include "FigureStandUpState.h"

#include "util/Bluetooth.h"
#include "control_state/FigureLineTraceState.h"
#include "control_state/StopState.h"

/**
 * コンストラクタ
 */
FigureStandUpState::FigureStandUpState() {

	Bluetooth::sendMessage("State changed : FigureStandUpState\n", 36);

	// メンバ初期化
	this->tail = Tail::getInstance();
	this->time = Time::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();
	this->lineMonitor = LineMonitor::getInstance();

	// execute(), next()
	this->startTime = this->time->getTime();

	// execute()
	this->referenceEncValue = this->balancingWalker->getRightEnc();

	// next()

	// その他

	// 初期処理
}

/**
 * デストラクタ
 */
FigureStandUpState::~FigureStandUpState() {
}

/**
 * 制御ステートに応じた制御を実行
 */
void FigureStandUpState::execute() {

	int forward = 0;
	int turn = 0;
	int angle = 110;

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
ControlState* FigureStandUpState::next() {

	// 前に倒れかけたら遷移
	if(110 < this->tail->getAngle()) {
		this->balancingWalker->init();
		return new StopState();
	}

	return this;
}
