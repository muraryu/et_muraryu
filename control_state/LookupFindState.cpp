/******************************************************************************
 *  LookupFindState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  Author: muraryu
 *****************************************************************************/

#include "LookupFindState.h"

#include "util/Bluetooth.h"
#include "control_state/LookupSitDownState.h"

#include "balancer_param.c"

/**
 * コンストラクタ
 */
LookupFindState::LookupFindState() {

	Bluetooth::sendMessage("State changed : LookupFindState\n", 33);

	// メンバ初期化
	this->tail = Tail::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();
	this->sonarSensor = SonarSensor::getInstance();
	this->lineMonitor = LineMonitor::getInstance();
	this->postureEstimation = PostureEstimation::getInstance();

	// execute(), next()

	// execute()

	// next()

	// その他
	//this->pidTurn = new PID(5,0,0);
	//this->pidTurn = new PID(mura_p,mura_i,mura_d);
	this->pidTurn = new PID(80,0,1200);

	// 初期処理
	this->balancingWalker->setStandControlMode(true);

	this->startDirection = this->postureEstimation->getDirection();

}

/**
 * デストラクタ
 */
LookupFindState::~LookupFindState() {
	delete this->pidTurn;
}

/**
 * 制御ステートに応じた制御を実行
 */
void LookupFindState::execute() {

	int forward = 40;
	int turn = 0;
	int angle = 80;

	/* 足の制御 */
	// 前進値、旋回値を設定
	//turn = (int)this->pidTurn->calc(this->startDirection,this->postureEstimation->getDirection(),-30,30); // test
	//this->pidTurn->setPID(mura_p,mura_i,mura_d);
	turn = (int)-this->pidTurn->calc(0.55,(double)this->lineMonitor->getAdjustedBrightness(),-100,100);
	// 足の制御実行
	balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
	// しっぽの制御実行
	this->tail->setCommandAngle(angle);

	//Bluetooth::sendMessage(this->balancingWalker->getLeftAngularVelocity());

}

/**
 * 制御ステート遷移条件
 * @return	ControlState* 遷移先クラスインスタンス
 * @note	遷移しないときはthisを返す
 */
ControlState* LookupFindState::next() {

	// ルックアップ検知で遷移
	Bluetooth::sendMessage(this->sonarSensor->getValue());
	if(this->sonarSensor->getValue() < 25) {
		this->balancingWalker->notifyGarageDistance(600);
		return new LookupSitDownState();
	}

	return this;
}
