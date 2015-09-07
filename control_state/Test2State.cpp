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
	this->pidTurnDirection = new PID(1,0,0);
	this->pidTurnLine = new PID(80,0,3000);

	// next()

	/* 初期処理 */
	this->balancingWalker->setStandControlMode(true);
	this->startTime = this->time->getTime();
	this->startDirection = this->postureEstimation->getDirection();

	this->turnflag = false;
	this->forward = 100;
	this->k_theta = 7.5;
}

/**
 * デストラクタ
 */
Test2State::~Test2State() {
	delete this->pidTurnDirection;
}

/**
 * 制御ステートに応じた制御を実行
 */
void Test2State::execute() {

	int forward = 100;
	int turn = 0;
	int angle = 0;

	/* 足の制御 */
	/*
	// 前進値、旋回値を設定

	// 徐々に加速パターン 加速中安定しにくい
	if(this->k_theta < 11.5) {
		this->k_theta += 0.008;
		K_THETADOT = this->k_theta;
		K_PHIDOT = 25.0F*1.1F;
		K_I = -0.14721F;
		turn = (int)this->pidTurnDirection->calc(this->startDirection,this->postureEstimation->getDirection(),-30,30); // test
	} else if(this->balancingWalker->getRightEnc() < 2500) {
		// 高速走行用ゲイン
		K_THETADOT = 11.5;
		K_PHIDOT = 25.0F*1.1F;
		K_I = -0.14721F;
		turn = (int)this->pidTurnDirection->calc(this->startDirection,this->postureEstimation->getDirection(),-30,30); // test
	} else if (this->balancingWalker->getRightEnc() < 4000) {
		// カーブ準備ゲイン
		K_THETADOT = 7.5;
		K_PHIDOT = 25.0F*1.5F;
		K_I = -0.14721F;
		turn = (int)this->pidTurnDirection->calc(this->startDirection,this->postureEstimation->getDirection(),-30,30); // test
	} else {
		//カーブ用ゲイン
		K_THETADOT = 11.5;
		K_PHIDOT = 25.0F*1.5F;
		K_I = -0.14721F;
		turn = (int)this->pidTurnDirection->calc(this->startDirection - 175,this->postureEstimation->getDirection(),-30,30); // test
	}*/

	/*
	// ステップ上に切り替えるパターン
	if(this->balancingWalker->getRightEnc() < 720) { // 出だしはゆっくり
		// 走行会２で用いた安定走行ゲイン
		K_THETADOT = 10.5;
		K_PHIDOT = 25.0F*1.1F;
		K_I = -0.14721F;
		forward = 60;
		turn = (int)this->pidTurnDirection->calc(this->startDirection,this->postureEstimation->getDirection(),-30,30); // test
	} else if(this->balancingWalker->getRightEnc() < 5500) { // あとから速く
		// 高速走行用ゲイン
		K_THETADOT = 10.5;
		K_PHIDOT = 25.0F*2.5F;
		K_I = -0.14721F;
		forward = 100;
		turn = (int)this->pidTurnDirection->calc(this->startDirection,this->postureEstimation->getDirection(),-30,30); // test
	} else if(this->balancingWalker->getRightEnc() < 6000) {
		// カーブ準備ゲイン
		K_THETADOT = 9.5;
		K_PHIDOT = 25.0F*1.1F;
		K_I = -0.14721F;
		turn = (int)this->pidTurnDirection->calc(this->startDirection,this->postureEstimation->getDirection(),-30,30); // test
	} else if(this->balancingWalker->getRightEnc() < 7500) { // テストカーブ
		// カーブゲイン
		K_THETADOT = 10.5;
		K_PHIDOT = 25.0F*2.5F;
		K_I = -0.14721F;
		turn = (int)this->pidTurnDirection->calc(this->startDirection - 175,this->postureEstimation->getDirection(),-30,30); // test
	}*/

	if(this->balancingWalker->getRightEnc() < 1080) { // 出だしはゆっくり
		// 走行会２で用いた安定走行ゲイン
		K_THETADOT = 7.5;
		K_PHIDOT = 25.0F;//*2.5F;
		K_I = -0.44721F;
		turn = (int)this->pidTurnDirection->calc(this->startDirection,this->postureEstimation->getDirection(),-30,30); // test
	} else if(this->balancingWalker->getRightEnc() < 5500) { // あとから速く
		// 高速走行用ゲイン
		K_THETADOT = 10.5;
		K_PHIDOT = 25.0F;//*2.5F;
		K_I = -0.44721F;
		this->forward = 100; //+= 0.03;
		this->turnflag;
		//forward = this->forward;
		turn = (int)this->pidTurnDirection->calc(this->startDirection,this->postureEstimation->getDirection(),-30,30); // test
	} else if(this->balancingWalker->getRightEnc() < 6000) { // カーブ準備
		// カーブ準備ゲイン
		K_THETADOT = 9.5;
		K_PHIDOT = 25.0F;//*2.5F;
		K_I = -0.44721F;
		forward = 70;
		turn = (int)this->pidTurnDirection->calc(this->startDirection,this->postureEstimation->getDirection(),-30,30); // test
	} else if(this->balancingWalker->getRightEnc() < 7500) { // テストカーブ
		// カーブゲイン
		K_THETADOT = 9.5;
		K_PHIDOT = 25.0F*2.5F;
		K_I = -0.44721F;
		turn = (int)this->pidTurnDirection->calc(this->startDirection - 175,this->postureEstimation->getDirection(),-30,30); // test
	} else {
		// 再直進
		K_THETADOT = 10.5;
		K_PHIDOT = 25.0F;//*2.5F;
		K_I = -0.44721F;
		turn = (int)this->pidTurnDirection->calc(this->startDirection - 175,this->postureEstimation->getDirection(),-30,30); // test
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
