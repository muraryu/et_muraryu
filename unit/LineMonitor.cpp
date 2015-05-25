/******************************************************************************
 *  LineMonitor.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/02/07
 *  Implementation of the Class Balancer
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/


#include "LineMonitor.h"

// 定数宣言
const S16 LineMonitor::INITIAL_THRESHOLD = 400;  // 黒色の光センサ値

/**
 * コンストラクタ
 * @param lightSensor 光センナ
 */
LineMonitor::LineMonitor(const ecrobot::LightSensor& lightSensor)
    : mLightSensor(lightSensor),
      mThreshold(INITIAL_THRESHOLD) {
}

/**
 * デストラクタ
 */
LineMonitor::~LineMonitor() {
}

/**
 * ライン上か否かを判定する
 * @retval true  ライン上
 * @retval false ライン外
 */
bool LineMonitor::isOnLine() const {
    // 光センサからの取得値を見て
    // 黒以上であれば「true」を、
    // そうでなければ「false」を返す
    if (mLightSensor.getBrightness() >= mThreshold) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * ライン閾値を設定する。
 * @param threshold ライン閾値
 */
void LineMonitor::setThreshold(S16 threshold) {
    mThreshold = threshold;
}
