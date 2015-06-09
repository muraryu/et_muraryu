/******************************************************************************
 *  BalancingWalker.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/09
 *  Definition of the Class BalancingWalker
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_UNIT_BALANCINGWALKER_H_
#define NXT_UNIT_BALANCINGWALKER_H_

#include "GyroSensor.h"
#include "Motor.h"
#include "Nxt.h"

#include "BalancerCpp.h"

class BalancingWalker {
public:
    virtual ~BalancingWalker();
    static BalancingWalker* getInstance();
    void init(const ecrobot::GyroSensor* gyroSensor,
            ecrobot::Motor* leftWheel,
            ecrobot::Motor* rightWheel,
            const ecrobot::Nxt* nxt,
            Balancer* balancer);
    void control();
    void BalancingWalker::setForwardTurn(int forward, int turn);

private:
    BalancingWalker();
    const ecrobot::GyroSensor* mGyroSensor;
    ecrobot::Motor* mLeftWheel;
    ecrobot::Motor* mRightWheel;
    const ecrobot::Nxt* mNxt;
    Balancer* mBalancer;
    S32 forward;
    S32 turn;

};

#endif  // NXT_UNIT_BALANCINGWALKER_H_
