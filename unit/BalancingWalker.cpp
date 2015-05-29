/******************************************************************************
 *  BalancingWalker.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/02/07
 *  Implementation of the Class BalancingWalker
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "BalancingWalker.h"

// 定数宣言
const int BalancingWalker::LOW    = 30;    // 低速
const int BalancingWalker::NORMAL = 50;    // 通常
const int BalancingWalker::HIGH   = 70;    // 高速

/**
 * コンストラクタ
 * @param gyroSensor ジャイロセンサ
 * @param leftWheel  左モータ
 * @param rightWheel 右モータ
 * @param nxt        NXTデバイス
 * @param balancer   バランサ
 */
BalancingWalker::BalancingWalker(const ecrobot::GyroSensor& gyroSensor,
                                 ecrobot::Motor& leftWheel,
                                 ecrobot::Motor& rightWheel,
                                 const ecrobot::Nxt& nxt,
                                 Balancer* balancer)
    : mGyroSensor(gyroSensor),
      mLeftWheel(leftWheel),
      mRightWheel(rightWheel),
      mNxt(nxt),
      mBalancer(balancer),
      mForward(LOW),
      mTurn(LOW) {
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
    S16 angle = mGyroSensor.getAnglerVelocity();  // ジャイロセンサ値
    S32 rightWheelEnc = mRightWheel.getCount();   // 右モータ回転角度
    S32 leftWheelEnc  = mLeftWheel.getCount();    // 左モータ回転角度

    mBalancer->setCommand(mForward, mTurn);

    mBalancer->update(angle, rightWheelEnc, leftWheelEnc, mNxt.getBattMv());

    // 左右モータに回転を指示する
    mLeftWheel.setPWM(mBalancer->getPwmLeft());
    mRightWheel.setPWM(mBalancer->getPwmRight());

}

/**
 * バランス走行に必要なものをリセットする
 */
void BalancingWalker::init() {
    int offset = mGyroSensor.getAnglerVelocity();  // ジャイロセンサ値

    // モータエンコーダをリセットする
    mLeftWheel.reset();
    mRightWheel.reset();

    // 倒立振子制御初期化
    mBalancer->init(offset);
}

/**
 * PWM値を設定する
 * @param forward 前進/後進命令。100(前進最大値)～-100(後進最大値)
 * @param turn    旋回命令。100(右旋回最大値)～-100(左旋回最大値)
 */
void BalancingWalker::setCommand(int forward, int turn) {
    mForward = forward;
    mTurn    = turn;
}
