/******************************************************************************
 *  FigureUpState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/23
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  フィギュアL段差のぼり
 *  とりあえず位置制御
 *  Author: muraryu
 *****************************************************************************/

#include "FigureUpState.h"

#include "util/Bluetooth.h"
#include "control_state/FigureLineTraceState.h"
#include "control_state/FigureStopState.h"
#include "control_state/FigureTailUpState.h"


/**
 * コンストラクタ
 */
FigureUpState::FigureUpState() {

	Bluetooth::sendMessage("State changed : FigureUpState\n", 31);

	// メンバ初期化
	this->balancingWalker = BalancingWalker::getInstance();
	this->tail = Tail::getInstance();

	// execute(), next()

	// execute()

	// next()

	// その他
	this->pid = new PID(0.06,0,0);

	// 初期処理
	this->startRightEnc = this->balancingWalker->getRightEnc();
}

/**
 * デストラクタ
 */
FigureUpState::~FigureUpState() {
	delete this->pid;
}

/**
 * 制御ステートに応じた制御を実行
 */
void FigureUpState::execute() {

	int forward = 60;
	int turn = 0;
	int angle = 105;

	/* 足の制御 */
	// 前進値、旋回値を設定
	//turn
	// 足の制御実行
	balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
	if(360 < this->balancingWalker->getRightEnc() - this->startRightEnc) {
	//angle = 110;
	}
	// しっぽの制御実行
	this->tail->setCommandAngle(angle);
}

/**
 * 制御ステート遷移条件
 * @return	ControlState* 遷移先クラスインスタンス
 * @note	遷移しないときはthisを返す
 */
ControlState* FigureUpState::next() {

	// 車輪が一定以上回転したら遷移
	if(270 < this->balancingWalker->getRightEnc() - this->startRightEnc) {
	//if(110 < this->tail->getAngle()) {
		//return new FigureLineTraceState();
		return new FigureStopState();
		//return new FigureTailUpState();
	}

	return this;
}
