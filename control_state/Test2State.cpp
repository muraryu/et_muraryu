/******************************************************************************
 *  Test2State.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/25
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  テスト用
 *  Author: muraryu
 *****************************************************************************/

#include "Test2State.h"

#include "util/Bluetooth.h"
#include "control_state/StopState.h"
#include "control_state/FigureFindState.h"
#include "control_state/GarageStopState.h"
#include "balancer_param.c"

/**
 * コンストラクタ
 */
Test2State::Test2State() {

	Bluetooth::sendMessage("State changed : Test2State\n", 28);

	/* メンバ初期化 */
	// シングルトン取得
	this->tail = Tail::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();
	this->lineMonitor = LineMonitor::getInstance();
	this->time = Time::getInstance();
	this->postureEstimation = PostureEstimation::getInstance();

	// execute(), next()

	// execute()
	this->pidTurn = new PID(1,0,0);
	this->pidTurnLine = new PID(80,0,3000);

	// next()

	/* 初期処理 */
	this->balancingWalker->setStandControlMode(true);
	this->startTime = this->time->getTime();
	this->startDirection = this->postureEstimation->getDirection();

	this->turnflag = false;
	this->forward = 70;
}

/**
 * デストラクタ
 */
Test2State::~Test2State() {
	delete this->pidTurn;
}

/**
 * 制御ステートに応じた制御を実行
 */
void Test2State::execute() {

	int turn = 0;
	int angle = 0;

	/* 足の制御 */
	// 前進値、旋回値を設定
	//turn = (int)-this->pidTurn->calc(0.55,this->lineMonitor->getAdjustedBrightness(),-100,100);	// サンプルコース

	if(6000 < this->balancingWalker->getRightEnc()) {
		if( -175 < this->postureEstimation->getDirection() && this->turnflag == false) {
			this->forward = 100;
			K_THETADOT = 7.5;
			K_PHIDOT = 25.0F*3.5F;
			turn = -30;
		}
		else {
			this->turnflag = true;
			this->forward = 100;
			K_THETADOT = 11.5;
			turn = (int)this->pidTurn->calc(this->startDirection-175,this->postureEstimation->getDirection(),-30,30); // test
		}
	}
	else if(1080 < this->balancingWalker->getRightEnc()){//100 < this->forward) {//11.0 < K_THETADOT) {
		this->forward = 100;
		K_THETADOT = 11.3;
		turn = (int)this->pidTurn->calc(this->startDirection,this->postureEstimation->getDirection(),-100,100); // test
	}
	else {
		this->forward =100;//+= 0.3;
		//K_THETADOT += 0.008;
		turn = (int)-this->pidTurnLine->calc(0.55,this->lineMonitor->getAdjustedBrightness(),-100,100);	// サンプルコース
	}


	// 足の制御実行
	balancingWalker->setForwardTurn(this->forward, turn);

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
ControlState* Test2State::next() {

	Bluetooth::sendMessage(this->balancingWalker->getRightEnc());
	// チョイ走る
	/*
	if(10.0 < this->time->getTime() - this->startTime ) {
		return new FigureFindState();
	}
	*/
	if(12000 < this->balancingWalker->getRightEnc()) {
		return new GarageStopState();
	}



	return this;
}
