/******************************************************************************
 *  FigureLineTraceState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/07/01
 *  ステートパターンConcrete
 *  フィギュアLに上ったあと停止位置までラインに追従する
 *  Author: muraryu
 *****************************************************************************/

#include "FigureLineTraceState.h"

#include "util/Bluetooth.h"
#include "control_state/GarageRApproachState.h"

/**
 * コンストラクタ
 */
FigureLineTraceState::FigureLineTraceState() {

	Bluetooth::sendMessage("State changed : FigureLineTraceState\n", 38);

	/* メンバ初期化 */
	// シングルトン取得
	this->balancingWalker = BalancingWalker::getInstance();
	this->tail = Tail::getInstance();
	this->lineMonitor = LineMonitor::getInstance();
	this->time = Time::getInstance();
	this->postureEstimation = PostureEstimation::getInstance();

	// execute(), next()

	// execute()
	this->pidTurn = new PID(100,0,600);
	this->pidForward = new PID(0.2,0,0);

	// next()

	/* 初期処理 */
	this->balancingWalker->setStandControlMode(true);
	this->startRightEnc = this->balancingWalker->getRightEnc();
	this->startDirection = this->postureEstimation->getDirection();
	this->startTime = this->time->getTime();
	this->stableTime = this->time->getTime();


}

/**
 * デストラクタ
 */
FigureLineTraceState::~FigureLineTraceState() {
	delete this->pidTurn;
	delete this->pidForward;
}

/**
 * 制御ステートに応じた制御を実行
 */
void FigureLineTraceState::execute() {

	int forward = 0;
	int turn = 0;
	int angle = 0;
	double direction = 0;

	/* 足の制御 */
	// 前進値、旋回値を設定
	if(this->time->getTime() - this->startTime < 3.0) { // 3秒待機して安定させる
		forward = (int)this->pidForward->calc(this->startRightEnc, this->balancingWalker->getRightEnc(), -100, 100);
		this->startDirection = this->postureEstimation->getDirection();
	}
	else { // 5秒後からライントレース
		forward = 10;
		turn = (int)-this->pidTurn->calc(0.5,this->lineMonitor->getAdjustedBrightness(),-100,100);
		direction = this->postureEstimation->getDirection() - this->startDirection;
		if(direction < -25 && turn < 0) {
			//Bluetooth::sendMessage(direction);
			turn = 0;
		}
		else if(25 < direction && 0 < turn) {
			//Bluetooth::sendMessage(1);
			turn = 0;
		}
	}

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
ControlState* FigureLineTraceState::next() {

	// ライントレースが安定して一定時間経過で遷移
	double currentBrightness = this->lineMonitor->getAdjustedBrightness();
	double currentTime = this->time->getTime();
	//Bluetooth::sendMessage(currentBrightness*100);
	if(0.35 < currentBrightness && currentBrightness < 0.65) { // 安定
		if(2.0 < currentTime - this->stableTime) {
			return new GarageRApproachState();
		}
	}
	else { // 不安定
		this->stableTime = currentTime;
	}

	return this;
}
