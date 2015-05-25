/******************************************************************************
 *  LineTracer.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/02/07
 *  Implementation of the Class LineTracer
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "LineTracer.h"

/**
 * コンストラクタ
 * @param lineMonitor     ライン判定
 * @param balancingWalker 倒立走行
 */
LineTracer::LineTracer(const LineMonitor* lineMonitor,
                       BalancingWalker* balancingWalker)
    : mLineMonitor(lineMonitor),
      mBalancingWalker(balancingWalker),
      mIsInitialized(FALSE) {
}

/**
 * デストラクタ
 */
LineTracer::~LineTracer() {
}

/**
 * ライントレースする
 */
void LineTracer::run() {
    if (mIsInitialized == FALSE) {
        mBalancingWalker->init();
        mIsInitialized = TRUE;
    }

    bool isOnLine = mLineMonitor->isOnLine();

    // 走行体の向きを計算する
    int direction = calcDirection(isOnLine);

    mBalancingWalker->setCommand(BalancingWalker::LOW, direction);

    // 倒立走行を行う
    mBalancingWalker->run();
}

/**
 * 走行体の向きを計算する
 * @param isOnLine true:ライン上/false:ライン外
 * @retval 30  ライン上にある場合(右旋回指示)
 * @retval -30 ライン外にある場合(左旋回指示)
 */
int LineTracer::calcDirection(bool isOnLine) {
    if (isOnLine) {
        // ライン上にある場合
        return BalancingWalker::LOW;
    } else {
        // ライン外にある場合
        return -BalancingWalker::LOW;
    }
}
