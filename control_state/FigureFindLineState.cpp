/******************************************************************************
 *  FigureFindLineState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/24
 *  制御ステートに応じた制御を行う
 *  ステートパターンConcrete
 *  フィギュアLスピン
 *  Author: muraryu
 *****************************************************************************/

#include "FigureFindLineState.h"

#include "util/Bluetooth.h"
#include "control_state/FigureDownState.h"

/**
 * コンストラクタ
 */
FigureFindLineState::FigureFindLineState() {

	Bluetooth::sendMessage("State changed : FigureFindLineState\n", 37);

	// メンバ初期化
	this->balancingWalker = BalancingWalker::getInstance();
	this->postureEstimation = PostureEstimation::getInstance();
	this->lineMonitor = LineMonitor::getInstance();

	// execute(), next()
	this->findFlag = false;
	// execute(

	// next()
	this->minBrightness = this->lineMonitor->getAdjustedBrightness();

	// その他

	// 初期処理
	this->startDirection = this->postureEstimation->getDirection();
}

/**
 * デストラクタ
 */
FigureFindLineState::~FigureFindLineState() {
}

/**
 * 制御ステートに応じた制御を実行
 */
void FigureFindLineState::execute() {

	int forward = 0;
	int turn = 0;
	double brightness = this->lineMonitor->getAdjustedBrightness();

	/* ライン左端発見の判断 */
	if(brightness < this->minBrightness) {
		this->minBrightness = brightness;
	}
	if(this->minBrightness*1.25 < brightness) {
		Bluetooth::sendMessage("LineFound\n", 11);
		this->findFlag = true;
	}

	/* 足の制御 */
	// 前進値、旋回値を設定
	if(this->findFlag == false) {
		forward = 20;
		turn = -20;
	} else {
		forward = 0;
		turn = -20;
	}
	// 足の制御実行
	this->balancingWalker->setForwardTurn(forward, turn);

	/* しっぽの制御 */
	// 角度目標値を設定
	// しっぽの制御実行


}

/**
 * 制御ステート遷移条件
 * @return	ControlState* 遷移先クラスインスタンス
 * @note	遷移しないときはthisを返す
 */
ControlState* FigureFindLineState::next() {
	ControlState* baseControlState = base::next();
	if(baseControlState != this) {
		return baseControlState;
	}
	/*
	 * ここまでコード編集禁止
	 * 以下に遷移条件を記述する
	 */

	double diff = this->postureEstimation->getDirection() - this->startDirection;
	if(this->findFlag == true && 0 < diff) { // 左旋回でライン見つけた後0度を超えるまで右旋回したら遷移
		return new FigureDownState();
	}

	return this;
}
