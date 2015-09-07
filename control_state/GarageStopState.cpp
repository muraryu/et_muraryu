/******************************************************************************
 *  GarageStopState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/07/28
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  尻尾で立って終了
 *  とりあえず位置制御
 *  Author: muraryu
 *****************************************************************************/

#include "GarageStopState.h"

#include "util/Bluetooth.h"

/**
 * コンストラクタ
 */
GarageStopState::GarageStopState() {

	Bluetooth::sendMessage("State changed : GarageStopState\n", 33);

	// メンバ初期化
	this->balancingWalker = BalancingWalker::getInstance();
	this->tail = Tail::getInstance();

	// execute(), next()

	// execute()

	// next()

	// その他

	// 初期処理
}

/**
 * デストラクタ
 */
GarageStopState::~GarageStopState() {
}

/**
 * 制御ステートに応じた制御を実行
 */
void GarageStopState::execute() {

	int forward = 0;
	int turn = 0;
	int angle = 85;

	/* 足の制御 */
	// 前進値、旋回値を設定
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
ControlState* GarageStopState::next() {

	//Bluetooth::sendMessage(this->balancingWalker->calcGarageDistance());

	// 終わり

	return this;
}
