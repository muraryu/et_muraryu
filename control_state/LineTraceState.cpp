/******************************************************************************
 *  LineTraceState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/05
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  ベーシックコースライントレース走行
 *  Author: muraryu
 *****************************************************************************/

#include "LineTraceState.h"

#include "util/Bluetooth.h"
#include "control_state/StopState.h"
#include "control_state/FigureFindState.h"
#include "control_state/LookupFindState.h"
#include "balancer_param.c"

/**
 * コンストラクタ
 */
LineTraceState::LineTraceState() {

	Bluetooth::sendMessage("State changed : LineTraceState\n", 32);

	// シングルトンインスタンス取得
	this->tail = Tail::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();
	this->lineMonitor = LineMonitor::getInstance();

	// インスタンス生成
	this->pid = new PID(80,0,3000);

	// 初期処理
	this->balancingWalker->setStandControlMode(true);

}

/**
 * デストラクタ
 */
LineTraceState::~LineTraceState() {
	delete this->pid;
}

/**
 * 制御ステートに応じた制御を実行
 */
void LineTraceState::execute() {

	int forward = 100;
	int turn = 0;
	int angle = 0;

	/* 足の制御 */
	// 前進値、旋回値を設定

	// チャンピオンシップ調整用
	/*
	K_THETADOTをコンストラクタで10.0に
	フィギュア段差スピード落とす
	if(this->balancingWalker->getRightEnc() < 1000) { // 出だしゆっくり
		forward = 70;
	} else {
		K_F[0] = -0.870303F;
		K_F[1] = -41.9978F;
		K_F[2] = -1.1566F;
		K_F[3] = -3.58873F;
		forward = 100;
	}*/

	//turn = (int)-this->pid->calc(0.5,this->lineMonitor->getAdjustedBrightness(),-100,100);

	// Lコースゴール前脱線するときは手前でトレース位置調整
	if(8000 < this->balancingWalker->getRightEnc()) {
		forward = 90;
	}
	if(this->balancingWalker->getRightEnc() < 10000) {
		turn = (int)-this->pid->calc(0.5,this->lineMonitor->getAdjustedBrightness(),-100,100);
	}
	else {
		turn = (int)-this->pid->calc(0.6,this->lineMonitor->getAdjustedBrightness(),-100,100);
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
ControlState* LineTraceState::next() {

	// 一定距離は知ったら（ゴールしたら）遷移
	// コースR フィギュア
/*	if(13000 <= this->balancingWalker->getRightEnc()) {
		return new FigureFindState();
	}*/


	// コースL ルックアップ
	//Bluetooth::sendMessage(this->balancingWalker->getRightEnc());

	if(12200 <= this->balancingWalker->getRightEnc()) {
			return new LookupFindState();
	}


	return this;
}
