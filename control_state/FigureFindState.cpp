/******************************************************************************
 *  FigureFindState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/24
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  Author: muraryu
 *****************************************************************************/

#include "FigureFindState.h"

#include "util/Bluetooth.h"
#include "util/Str.h"
#include "control_state/FigureSitDownState.h"


/**
 * コンストラクタ
 */
FigureFindState::FigureFindState() {

	Bluetooth::sendMessage("State changed : FigureFindState\n", 33);

	/* メンバ初期化 */
	// シングルトン取得
	this->balancingWalker = BalancingWalker::getInstance();
	this->lineMonitor = LineMonitor::getInstance();

	// execute(), next()

	// execute()
	this->pid = new PID(80,0,200);

	// next()

	/* 初期処理 */

}

/**
 * デストラクタ
 */
FigureFindState::~FigureFindState() {
	delete this->pid;
}

/**
 * 制御ステートに応じた制御を実行
 */
void FigureFindState::execute() {

	int forward = 30;
	int turn = 0;

	/* 足の制御 */
	// 前進値、旋回値を設定
	turn = (int)-this->pid->calc(0.60,(double)this->lineMonitor->getAdjustedBrightness(),-100,100);	// サンプルコース
	// 足の制御実行
	balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
	// しっぽの制御実行

}

/**
 * 制御ステート遷移条件
 * @return	ControlState* 遷移先クラスインスタンス
 * @note	遷移しないときはthisを返す
 */
ControlState* FigureFindState::next() {

	// フィギュアＬ段差にぶつかったら遷移
	// 両足モーター角速度deg/secが0になったら遷移する
	// 失敗する場合はジャイロセンサも使う
	if(this->balancingWalker->getRightAngularVelocity() < -0 && this->balancingWalker->getLeftAngularVelocity() < -0) {
		return new FigureSitDownState();
	}

	return this;
}
