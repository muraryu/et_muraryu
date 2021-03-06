/******************************************************************************
 *  PostureEstimation.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/29
 *  ロボットの姿勢推定と管理
 *  モーターエンコーダーがリセットされると車輪周速度計算がダメになるため方位計算もおかしくなる
 *  シングルトン
 *  Author: muraryu
 *****************************************************************************/

#include "PostureEstimation.h"

#include "util/Bluetooth.h"

bool PostureEstimation::insFlag = false;
PostureEstimation* PostureEstimation::instance;

/**
 * コンストラクタ
 */
PostureEstimation::PostureEstimation()
{
	//
	this->wheelWidth = 0.165;
	this->interval = 0.004;

	// メンバ初期化
	this->posX = 0;
	this->posY = 0;
	this->direction = 0;
}

/**
 * デストラクタ
 */
PostureEstimation::~PostureEstimation() {
}

/**
 * インスタンス取得
 */
PostureEstimation* PostureEstimation::getInstance() {
	if(insFlag == false){
		PostureEstimation::instance = new PostureEstimation();
		insFlag = true;
	}
	return PostureEstimation::instance;
}

/**
 * インスタンス初期化
 */
void PostureEstimation::init(BalancingWalker* balancingWalker, ecrobot::GyroSensor* gyroSensor) {

	// メンバ初期化
	this->balancingWalker = balancingWalker;
	this->gyroSensor = gyroSensor;

}

/**
 * 姿勢状態を推定して更新
 */
void PostureEstimation::update() {
	// 方位[deg] TODO 回転速度を誰に聞くか TODO 周速度あたりの計算おかしい 0.05
	this->direction += (this->balancingWalker->getLeftAngularVelocity() - this->balancingWalker->getRightAngularVelocity()) / this->wheelWidth * this->interval * 0.04002;
	//Bluetooth::sendMessage(this->direction);
	this->tilt += this->interval * (this->gyroSensor->getAnglerVelocity() + 6.00);
	//Bluetooth::sendMessage(this->tilt*100);
}

/**
 * x座標[m]を取得
 */
double PostureEstimation::getPosX() {
	return this->posX;
}

/**
 * y座標[m]を取得
 */
double PostureEstimation::getPosY() {
	return this->posY;
}

/**
 * 方位[deg]を取得
 */
double PostureEstimation::getDirection() {
	return this->direction;
}

double PostureEstimation::getTilt() {
	return this->tilt;
}
