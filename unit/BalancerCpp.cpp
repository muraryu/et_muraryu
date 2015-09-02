/******************************************************************************
 *  BalancerCpp.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/02/07
 *  Implementation of the Class Balancer
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

extern "C" {
#include "balancer.h"  // 倒立振子制御用ヘッダファイル
}
#include "BalancerCpp.h"

/**
 * コンストラクタ
 */
Balancer::Balancer()
    : mForward(0),
      mTurn(0),
      mOffset(0),
      mRightPwm(0),
      mLeftPwm(0) {
}

/**
 * デストラクタ
 */
Balancer::~Balancer() {
}

/**
 * バランサを初期化する
 * @param offset ジャイロセンサオフセット値
 */
void Balancer::init(int offset) {
    mOffset = offset;
    balance_init();  // 倒立振子制御初期化
}

/**
 * バランサの値を更新する
 * @param angle   角速度
 * @param rwEnc   右車輪エンコーダ値
 * @param lwEnc   左車輪エンコーダ値
 * @param battety バッテリ電圧値
 */
void Balancer::update(int angle, int rwEnc, int lwEnc, int battery) {
    // 倒立振子制御APIを呼び出し、倒立走行するための
    // 左右モータ出力値を得る
    balance_control(
        static_cast<F32>(mForward),
        static_cast<F32>(mTurn),
        static_cast<F32>(angle),
        static_cast<F32>(mOffset),
        static_cast<F32>(lwEnc),
        static_cast<F32>(rwEnc),
        static_cast<F32>(battery),
        &mLeftPwm,
        &mRightPwm);
}

/**
 * PWM値を設定する
 * @param forward 前進/後進命令。100(前進最大値)～-100(後進最大値)
 * @param turn    旋回命令。100(右旋回最大値)～-100(左旋回最大値)
 */
void Balancer::setCommand(int forward, int turn) {
    mForward = forward;
    mTurn    = turn;
}

/**
 * 右車輪のPWM値を取得する
 * @return 右車輪のPWM値
 */
S8 Balancer::getPwmRight() {

	S8 ret = mRightPwm;
	if(ret < -100) {
		ret = -100;
	}
	else if(100 < ret) {
		ret = 100;
	}
	return ret;

    return mRightPwm;
}

/**
 * 左車輪のPWM値を取得する
 * @return 左車輪のPWM値
 */
S8 Balancer::getPwmLeft() {

	S8 ret = mLeftPwm;
	if(ret < -100) {
		ret = -100;
	}
	else if(100 < ret) {
		ret = 100;
	}
	return ret;


    return mLeftPwm;
}
