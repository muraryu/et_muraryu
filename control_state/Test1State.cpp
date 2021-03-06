/******************************************************************************
 *  Test1State.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/25
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  テスト用
 *  Author: muraryu
 *****************************************************************************/

#include "Test1State.h"

#include "util/Bluetooth.h"
#include "control_state/StopState.h"
#include "control_state/FigureFindState.h"
#include "control_state/GarageStopState.h"
#include "control_state/LookupSitDownState.h"
#include "balancer_param.c"

/**
 * コンストラクタ
 */
Test1State::Test1State() {

	Bluetooth::sendMessage("State changed : Test1State\n", 28);

	// シングルトンインスタンス取得
	this->tail = Tail::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();
	this->lineMonitor = LineMonitor::getInstance();
	this->time = Time::getInstance();
	this->postureEstimation = PostureEstimation::getInstance();

	// インスタンス生成
	this->pidTurn = new PID(1,0,0);
	//this->pidTurn = new PID(80,0,3000);

	// 初期処理
	this->balancingWalker->setStandControlMode(true);
	this->startTime = this->time->getTime();
	this->startDirection = this->postureEstimation->getDirection();
	this->turnflag = false;

	K_THETADOT = 10.0;

}

/**
 * デストラクタ
 */
Test1State::~Test1State() {
	delete this->pidTurn;
}

/**
 * 制御ステートに応じた制御を実行
 */
void Test1State::execute() {

	int forward = 100;
	int turn = 0;
	int angle = 0;

	/* 足の制御 */
	// 前進値、旋回値を設定
	if(this->balancingWalker->getRightEnc() < 1000) {
		K_THETADOT = 10.0;//7.5;
		forward = 70;
	} else {
		K_THETADOT = 10.0;
		K_F[0] = -0.870303F;
		K_F[1] = -41.9978F;
		K_F[2] = -1.1566F;
		K_F[3] = -3.58873F;
		//forward = 100;
	}
	turn = (int)this->pidTurn->calc(this->startDirection,this->postureEstimation->getDirection(),-100,100); // test
	//turn = (int)-this->pidTurn->calc(0.55,this->lineMonitor->getAdjustedBrightness(),-100,100);	// サンプルコース

	// 往復
	if(4000 < this->balancingWalker->getRightEnc()) {
		if( -175 < this->postureEstimation->getDirection() && turnflag == false) {
			forward = 100;
			turn = -20;
		}
		else {
			turnflag = true;
			forward = 100;
			turn = (int)this->pidTurn->calc(this->startDirection-175,this->postureEstimation->getDirection(),-30,30); // test
		}
	}
	else {
		turn = (int)this->pidTurn->calc(this->startDirection,this->postureEstimation->getDirection(),-100,100); // test
	}
	if(6000 < this->balancingWalker->getRightEnc()) {
		forward = 30;
		angle = 80;
	}

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
ControlState* Test1State::next() {

	Bluetooth::sendMessage(this->balancingWalker->getRightEnc());
	// チョイ走る
	/*
	if(10.0 < this->time->getTime() - this->startTime ) {
		return new FigureFindState();
	}
	*/
	if(7000 < this->balancingWalker->getRightEnc()) {
		return new LookupSitDownState();
	}



	return this;
}
