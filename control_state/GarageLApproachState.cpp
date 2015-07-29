/******************************************************************************
 *  GarageLApproachState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/23
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  フィギュアL段差のぼり
 *  とりあえず位置制御
 *  Author: muraryu
 *****************************************************************************/

#include "GarageLApproachState.h"

#include "util/Bluetooth.h"
#include "control_state/GarageStopState.h"

/**
 * コンストラクタ
 */
GarageLApproachState::GarageLApproachState() {

	Bluetooth::sendMessage("State changed : GarageLApproachState\n", 38);

	// メンバ初期化
	this->balancingWalker = BalancingWalker::getInstance();
	this->tail = Tail::getInstance();
	this->pidTurn = new PID(5,0,0);
	this->postureEstimation = PostureEstimation::getInstance();
	this->lineMonitor = LineMonitor::getInstance();

	// execute(), next()

	// execute()

	// next()

	// その他

	// 初期処理
	this->startDirection = this->postureEstimation->getDirection();
	this->startRightEnc = this->balancingWalker->getRightEnc();
	this->figureEndRightEnc = this->startRightEnc + 36000; // 適当に大きい値で初期化
	this->figureEndFlag = false;
}

/**
 * デストラクタ
 */
GarageLApproachState::~GarageLApproachState() {
	delete this->pidTurn;
}

/**
 * 制御ステートに応じた制御を実行
 */
void GarageLApproachState::execute() {

	int forward = 40;
	int turn = 0;
	int angle = 0;

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
ControlState* GarageLApproachState::next() {

	//

	return this;
}
