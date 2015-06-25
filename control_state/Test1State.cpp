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

/**
 * コンストラクタ
 */
Test1State::Test1State() {

	Bluetooth::sendMessage("State changed : Test1State\n", 28);

	/* メンバ初期化 */
	// シングルトン取得
	this->tail = Tail::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();
	this->lineMonitor = LineMonitor::getInstance();
	this->time = Time::getInstance();

	// execute(), next()

	// execute()
	this->pid = new PID(240,0,0);

	// next()

	/* 初期処理 */
	this->balancingWalker->setStandControlMode(true);
	this->startTime = this->time->getTime();

}

/**
 * デストラクタ
 */
Test1State::~Test1State() {
	delete this->pid;
}

/**
 * 制御ステートに応じた制御を実行
 */
void Test1State::execute() {

	int forward = 40;
	int turn = 0;
	int angle = 0;

	/* 足の制御 */
	// 前進値、旋回値を設定
	turn = -this->pid->calc(0.22,(double)this->lineMonitor->getBrightness(),-100,100);	// サンプルコース
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
ControlState* Test1State::next() {
	ControlState* baseControlState = base::next();
	if(baseControlState != this) {
		return baseControlState;
	}
	/*
	 * ここまでコード編集禁止
	 * 以下に遷移条件を記述する
	 */

	// チョイ走る
	if(3.0 < this->time->getTime() - this->startTime ) {
		return new FigureFindState();
	}


	return this;
}
