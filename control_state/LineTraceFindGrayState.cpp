/******************************************************************************
 *  LineTraceFindGrayState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/05
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  Author: muraryu
 *****************************************************************************/

#include "LineTraceFindGrayState.h"

#include "util/Bluetooth.h"
#include "control_state/StopState.h"

/**
 * コンストラクタ
 */
LineTraceFindGrayState::LineTraceFindGrayState() {

	Bluetooth::sendMessage("State changed : LineTraceFindGrayState\n", 40);

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
LineTraceFindGrayState::~LineTraceFindGrayState() {
	delete this->pid;
}

/**
 * 制御ステートに応じた制御を実行
 */
void LineTraceFindGrayState::execute() {

	int forward = 20;
	int turn = 0;
	int angle = 0;

	/* 足の制御 */
	// 前進値、旋回値を設定
	turn = (int)-this->pid->calc(0.5,this->lineMonitor->getAdjustedBrightness(),-100,100);
	// 足の制御実行
	balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
	// しっぽの制御実行
	this->tail->setCommandAngle(angle);

}

/**
 * 制御ステート遷移条件 TODO 制御モードに変更 あと継承やめてインターフェースに
 * @return	ControlState* 遷移先クラスインスタンス
 * @note	遷移しないときはthisを返す
 */
ControlState* LineTraceFindGrayState::next() {

	// グレーライン検出で遷移


	return this;
}
