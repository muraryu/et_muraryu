/******************************************************************************
 *  FigureSitDownState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  Author: muraryu
 *****************************************************************************/

#include "FigureSitDownState.h"

#include "util/Bluetooth.h"
#include "control_state/TailStandDownState.h"

/**
 * コンストラクタ
 */
FigureSitDownState::FigureSitDownState() {

	Bluetooth::sendMessage("State changed : FigureSitDownState\n", 36);

	// メンバ初期化
	this->tail = Tail::getInstance();
	this->time = Time::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();

	// execute(), next()
	this->startTime = this->time->getTime();

	// execute()
	this->referenceEncValue = this->balancingWalker->getRightEnc();

	// next()

	// その他
	this->pid = new PID(0.2,0,0);

	// 初期処理
	this->balancingWalker->setStandControlMode(false);
}

/**
 * デストラクタ
 */
FigureSitDownState::~FigureSitDownState() {
	delete this->pid;
}

/**
 * 制御ステートに応じた制御を実行
 */
void FigureSitDownState::execute() {

	int forward = 0;
	int turn = 0;
	int angle = 100;

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
ControlState* FigureSitDownState::next() {
	ControlState* baseControlState = base::next();
	if(baseControlState != this) {
		return baseControlState;
	}
	/*
	 * ここまでコード編集禁止
	 * 以下に遷移条件を記述する
	 */


	// 経過時間で遷移
	/*
	if(5.5 < this->time->getTime() - this->startTime) {
		return new TailStandDownState();
	}
	*/
	return this;
}
