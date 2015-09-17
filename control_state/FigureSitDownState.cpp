/******************************************************************************
 *  FigureSitDownState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  フィギュアL段差発見で座る
 *  Author: muraryu
 *****************************************************************************/

#include "FigureSitDownState.h"

#include "util/Bluetooth.h"
#include "control_state/FigureUpState.h"
#include "control_state/FigureBackState.h"

/**
 * コンストラクタ
 */
FigureSitDownState::FigureSitDownState() {

	Bluetooth::sendMessage("State changed : FigureSitDownState\n", 36);

	// シングルトンインスタンス取得
	this->tail = Tail::getInstance();
	this->time = Time::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();
	this->lineMonitor = LineMonitor::getInstance();

	// インスタンス生成
	this->pid = new PID(0.2,0,0);

	// 初期処理
	this->balancingWalker->setStandControlMode(false);
	this->startTime = this->time->getTime();
	this->referenceEncValue = this->balancingWalker->getRightEnc();

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
	int angle = 90;

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
ControlState* FigureSitDownState::next() {

	// 経過時間で遷移

	if(2.0 < this->time->getTime() - this->startTime) {
		//return new FigureUpState();
		return new FigureBackState();
	}

	return this;
}
