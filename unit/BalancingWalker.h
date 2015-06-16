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
    void init();
    void control();
    void setForwardTurn(int forward, int turn);
    int getRunningDistance();
    void setStandControlMode(bool b);
    int getEnc();


private:
    BalancingWalker();

	static bool insFlag;
	static BalancingWalker* instance;

    const ecrobot::GyroSensor* mGyroSensor;
    ecrobot::Motor* mLeftWheel;
    ecrobot::Motor* mRightWheel;
    const ecrobot::Nxt* mNxt;
    Balancer* mBalancer;
    S32 forward;
    S32 turn;
    bool standControlMode;
    int offset;
    S32 rightWheelEncOffset;
    S32 leftWheelEncOffset;
    S32 rightWheelEnc;
    S32 leftWheelEnc;

};

#endif  // NXT_UNIT_BALANCINGWALKER_H_
