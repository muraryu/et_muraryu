/******************************************************************************
 *  GarageRecoveryState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/23
 *  Definition of the Class GarageRecoveryState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_GARAGERECOVERYSTATE_H_
#define NXT_CONTROL_STATE_GARAGERECOVERYSTATE_H_

#include "control_state/ControlState.h"
#include "unit/balancingWalker.h"
#include "util/Time.h"
#include "app/Tail.h"
#include "app/PostureEstimation.h"

class GarageRecoveryState : public ControlState {
	typedef ControlState base;

public:
	GarageRecoveryState();
	virtual ~GarageRecoveryState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	BalancingWalker* balancingWalker;
	Tail* tail;
	PostureEstimation* postureEstimation;
	PID* pidTurn;
	Time* time;

	int forward;
	double startDirection;
	double startTime;
	int startRightEnc;
	int garageEndRightEnc;

	bool turnFlag1;
	bool turnFlag2;
	bool endFlag;

};

#endif  // NXT_CONTROL_STATE_GARAGERECOVERYSTATE_H_
