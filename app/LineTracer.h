/******************************************************************************
 *  LineTracer.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/02/07
 *  Definition of the Class LineTracer
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef NXT_APP_LINETRACER_H_
#define NXT_APP_LINETRACER_H_

#include "LineMonitor.h"
#include "BalancingWalker.h"

class LineTracer {
public:
    LineTracer(const LineMonitor* lineMonitor,
               BalancingWalker* balancingWalker);
    virtual ~LineTracer();

    void run();

private:
    const LineMonitor* mLineMonitor;
    BalancingWalker* mBalancingWalker;
    bool mIsInitialized;

    int calcDirection(bool isOnLine);
};

#endif  // NXT_APP_LINETRACER_H_
