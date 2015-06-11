/******************************************************************************
 *  TailStandState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  制御パターンに応じた制御を行う
 *  ステートパターンConcrete
 *  Author: muraryu
 *****************************************************************************/

#include "TailStandState.h"

#include "util/Bluetooth.h"
#include "control_state/TailWalkState.h"

/**
 * コンストラクタ
 */
TailStandState::TailStandState() {

	Bluetooth::sendMessage("State changed : TailStandState\n", 32);

	// メンバ初期化
	// シングルトンではなく、Driverから受け取るか、仲介クラスからとるのもあり
	this->tail = Tail::getInstance();
	this->balancingWalker = BalancingWalker::getInstance();
}

/**
 * デストラクタ
 */
TailStandState::~TailStandState() {
}

/**
 * 制御パターンに応じた制御を実行
 */
void TailStandState::execute() {

	int forward = 0;
	int turn = 0;
	static double angle = 100;
	static int count = 0;
	static int satValue = 0;
	static bool flag = false;
	static bool flag2 = false;

	/* 足の制御 */
	// 前進値、旋回値を設定
	balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
	if(flag == false) {
		if(satValue == this->tail->getAngle()) {
			if(count < 500) {
				count++;
			}
			else {
				flag = true;
			}
		}
		else {
			satValue = this->tail->getAngle();
			count = 0;
		}
	}
	else {
		angle -= 0.06;
		if(angle < 74) {
			angle = 74;
			flag2 = true;
		}
	}

	this->tail->setCommandAngle((int)angle);

}

/**
 * 制御パターン遷移条件
 * @return	ControlState*
 * @note	遷移しないときはthisを返す
 */
ControlState* TailStandState::next() {

	static float satTime = 0.0;
	static int satValue = 0;
	int angle = this->tail->getAngle();

	// しっぽ停止時間計算 TODO 時刻クラス作る
	if(satValue == angle) {
		satTime += 0.004;
	}
	else {
		satValue = angle;
	}

	// しっぽが3秒間停止したら遷移
	if(3.0 < satTime) {
		return new TailWalkState();
	}

	return this;
}
