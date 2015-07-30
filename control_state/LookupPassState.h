/******************************************************************************
 *  LookupPassState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  Definition of the Class LookupPassState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_LOOKUPPASSSTATE_H_
#define NXT_CONTROL_STATE_LOOKUPPASSSTATE_H_

#include "control_state/ControlState.h"
#include "app/Tail.h"
#include "app/PostureEstimation.h"
#include "unit/balancingWalker.h"
#include "util/Time.h"
#include "util/PID.h"

class LookupPassState : public ControlState {
	typedef ControlState base;

public:
	LookupPassState();
	virtual ~LookupPassState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	BalancingWalker* balancingWalker;
	Time* time;
	PostureEstimation* postureEstimation;
	PID* pidTurn;

	double startTime;
	int startRightEnc;
	double startDirection;
	bool backFlag;
	int forward;

};

#endif  // NXT_CONTROL_STATE_LOOKUPPASSSTATE_H_
