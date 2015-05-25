/******************************************************************************
 *  LineMonitor.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/02/07
 *  Definition of the Class LineMonitor
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef NXT_UNIT_LINEMONITOR_H_
#define NXT_UNIT_LINEMONITOR_H_

#include "LightSensor.h"

// 定義
class LineMonitor {
public:
    explicit LineMonitor(const ecrobot::LightSensor& lightSensor);
    virtual ~LineMonitor();

    bool isOnLine() const;
    void setThreshold(S16 threshold);

private:
    static const S16 INITIAL_THRESHOLD;

    const ecrobot::LightSensor& mLightSensor;
    S16 mThreshold;
};

#endif  // NXT_UNIT_LINEMONITOR_H_
