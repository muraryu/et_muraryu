/******************************************************************************
 *  BalancingWalker.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/02/07
 *  Definition of the Class BalancingWalker
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef NXT_UNIT_BALANCINGWALKER_H_
#define NXT_UNIT_BALANCINGWALKER_H_

#include "GyroSensor.h"
#include "Motor.h"
#include "Nxt.h"

#include "BalancerCpp.h"

class BalancingWalker {
public:
    static const int LOW;
    static const int NORMAL;
    static const int HIGH;

    BalancingWalker(const ecrobot::GyroSensor& gyroSensor,
                    ecrobot::Motor& leftWheel,
                    ecrobot::Motor& rightWheel,
                    const ecrobot::Nxt& nxt,
                    Balancer* balancer);
    virtual ~BalancingWalker();

    void init();
    void run();
    void setCommand(int forward, int turn);

private:
    const ecrobot::GyroSensor& mGyroSensor;
    ecrobot::Motor& mLeftWheel;
    ecrobot::Motor& mRightWheel;
    const ecrobot::Nxt& mNxt;
    Balancer* mBalancer;
    int mForward;
    int mTurn;
};

#endif  // NXT_UNIT_BALANCINGWALKER_H_
