/******************************************************************************
 *  FigureBackState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/23
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  フィギュアL段差のぼり
 *  とりあえず位置制御
 *  Author: muraryu
 *****************************************************************************/

#include "FigureBackState.h"

#include "util/Bluetooth.h"
#include "control_state/FigureUpState.h"


/**
 * コンストラクタ
 */
FigureBackState::FigureBackState() {

	Bluetooth::sendMessage("State changed : FigureBackState\n", 33);

	// メンバ初期化
	this->balancingWalker = BalancingWalker::getInstance();
	this->tail = Tail::getInstance();
	this->postureEstimation = PostureEstimation::getInstance();

	// execute(), next()

	// execute()

	// next()

	// その他
	this->pidTurn = new PID(5,0,0);

	// 初期処理
	this->startRightEnc = this->balancingWalker->getRightEnc();
	this->startDirection = this->postureEstimation->getDirection();
}

/**
 * デストラクタ
 */
FigureBackState::~FigureBackState() {
	delete this->pidTurn;
}

/**
 * 制御ステートに応じた制御を実行
 */
void FigureBackState::execute() {

	int forward = -20;
	int turn = 0;
	int angle = 90;

	/* 足の制御 */
	// 前進値、旋回値を設定
	turn = this->pidTurn->calc(this->startDirection,this->postureEstimation->getDirection(),-30,30);
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
ControlState* FigureBackState::next() {

	// 車輪が一定以上回転したら遷移
	if(this->balancingWalker->getRightEnc() - this->startRightEnc < -180) {
		return new FigureUpState();
	}

	return this;
}
