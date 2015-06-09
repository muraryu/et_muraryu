/******************************************************************************
 *  BalancingWalker.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/02/07
 *  Implementation of the Class BalancingWalker
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "BalancingWalker.h"

DeclareResource(resource1);

/**
 * コンストラクタ
 * @param gyroSensor ジャイロセンサ
 * @param leftWheel  左モータ
 * @param rightWheel 右モータ
 * @param nxt        NXTデバイス
 * @param balancer   バランサ
 */
BalancingWalker::BalancingWalker(const ecrobot::GyroSensor* gyroSensor,
                                 ecrobot::Motor* leftWheel,
                                 ecrobot::Motor* rightWheel,
                                 const ecrobot::Nxt* nxt,
                                 Balancer* balancer) {
	this->mGyroSensor 	= gyroSensor;
	this->mLeftWheel 	= leftWheel;
	this->mRightWheel 	= rightWheel;
	this->mNxt 			= nxt;
	this->mBalancer 	= balancer;
	this->forward 		= 0;
	this->turn 			= 0;
}

/**
 * デストラクタ
 */
BalancingWalker::~BalancingWalker() {
}

/**
 * バランス走行する。
 */
void BalancingWalker::run() {
    S16 angle = mGyroSensor->getAnglerVelocity();  // ジャイロセンサ値
    S32 rightWheelEnc = mRightWheel->getCount();   // 右モータ回転角度
    S32 leftWheelEnc  = mLeftWheel->getCount();    // 左モータ回転角度

    GetResource(resource1);
    mBalancer->setCommand(this->forward, this->turn);
    ReleaseResource(resource1);

    mBalancer->update(angle, rightWheelEnc, leftWheelEnc, mNxt->getBattMv());

    // 左右モータに回転を指示する
    mLeftWheel->setPWM(mBalancer->getPwmLeft());
    mRightWheel->setPWM(mBalancer->getPwmRight());

}

/**
 * バランス走行に必要なものをリセットする
 * コンストラクタでやれば？
 */
void BalancingWalker::init() {
    int offset = mGyroSensor->getAnglerVelocity();  // ジャイロセンサ値

    // モータエンコーダをリセットする
    mLeftWheel->reset();
    mRightWheel->reset();

    // 倒立振子制御初期化
    mBalancer->init(offset);
}

/**
 * 前進、旋回の指令値をセットする
 * @param forward 前進値
 * @param turn    旋回値
 */
void BalancingWalker::setForwardTurn(S32 forward, S32 turn) {
    GetResource(resource1);
	this->forward = forward;
	this->turn = turn;
    ReleaseResource(resource1);
}
