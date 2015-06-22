/******************************************************************************
 *  LineTraceState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/05
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  Author: muraryu
 *****************************************************************************/

#include "LineTraceState.h"

#include "util/Bluetooth.h"
#include "control_state/StopState.h"

/**
 * コンストラクタ
 */
LineTraceState::LineTraceState() {

	Bluetooth::sendMessage("State changed : LineTraceState\n", 32);

	/* メンバ初期化 */
	// シングルトン取得
	this->tail = Tail::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();
	this->lineMonitor = LineMonitor::getInstance();

	// execute(), next()

	// execute()
	this->pid = new PID(240,0,0);

	// next()

	/* 初期処理 */
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

	int forward = 40;
	int turn = 0;
	int angle = 0;


	/*int test = this->lineMonitor->getBrightness();
	if (test < 100) {
		Bluetooth::sendMessage("100\n", 5);
	}else if(100 <= test && test < 200) {
		Bluetooth::sendMessage("200\n", 5);
	}else if(200 <= test && test < 300) {
		Bluetooth::sendMessage("300\n", 5);
	}else if(300 <= test && test < 400) {
		Bluetooth::sendMessage("400\n", 5);
	}else if(400 <= test && test < 500) {
		Bluetooth::sendMessage("500\n", 5);
	}else if(500 <= test && test < 600) {
		Bluetooth::sendMessage("600\n", 5);
	}else if(600 <= test && test < 700) {
		Bluetooth::sendMessage("700\n", 5);
	}else if(700 <= test && test < 800) {
		Bluetooth::sendMessage("800\n", 5);
	}else if(800 <= test && test < 900) {
		Bluetooth::sendMessage("900\n", 5);
	}else if(900 <= test && test < 1000) {
		Bluetooth::sendMessage("1000\n", 6);
	}*/

	/* 足の制御 */
	// 前進値、旋回値を設定
	turn = -this->pid->calc(0.22,(double)this->lineMonitor->getBrightness(),-100,100);
	//turn = -this->pid->calc(0.49,(double)this->lineMonitor->getBrightness()/1000,-100,100);
	/*
	if (turn < 10) {
		Bluetooth::sendMessage("10\n", 4);
	}else if(10 <= turn && turn < 20) {
		Bluetooth::sendMessage("20\n", 4);
	}else if(20 <= turn && turn < 30) {
		Bluetooth::sendMessage("30\n", 4);
	}else if(30 <= turn && turn < 40) {
		Bluetooth::sendMessage("40\n", 4);
	}else if(40 <= turn && turn < 50) {
		Bluetooth::sendMessage("50\n", 4);
	}else if(50 <= turn && turn < 60) {
		Bluetooth::sendMessage("60\n", 4);
	}else if(60 <= turn && turn < 70) {
		Bluetooth::sendMessage("70\n", 4);
	}else if(70 <= turn && turn < 80) {
		Bluetooth::sendMessage("80\n", 4);
	}else if(80 <= turn && turn < 90) {
		Bluetooth::sendMessage("90\n", 4);
	}else if(90 <= turn && turn < 100) {
		Bluetooth::sendMessage("100\n", 5);
	}
	*/
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
ControlState* LineTraceState::next() {
	ControlState* baseControlState = base::next();
	if(baseControlState != this) {
		return baseControlState;
	}
	/*
	 * ここまでコード編集禁止
	 * 以下に遷移条件を記述する
	 */



	return this;
}
