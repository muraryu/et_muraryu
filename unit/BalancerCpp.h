/******************************************************************************
 *  BalancerCpp.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/02/07
 *  Definition of the Class Balancer
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef NXT_UNIT_BALANCERCPP_H_
#define NXT_UNIT_BALANCERCPP_H_

class Balancer {
public:
    Balancer();
    virtual ~Balancer();

    void init(int offset);
    void update(int angle, int rwEnc, int lwEnc, int battery);
    void setCommand(int forward, int turn);
    S8 getPwmRight();
    S8 getPwmLeft();

private:
    int mForward;
    int mTurn;
    int mOffset;
    S8  mRightPwm;
    S8  mLeftPwm;
};

#endif  // NXT_UNIT_BALANCERCPP_H_
