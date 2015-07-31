/******************************************************************************
 *  GarageLApproachState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/07/28
 *  Definition of the Class GarageLApproachState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_GARAGELAPPROACHSTATE_H_
#define NXT_CONTROL_STATE_GARAGELAPPROACHSTATE_H_

#include "control_state/ControlState.h"
#include "unit/balancingWalker.h"
#include "app/Tail.h"
#include "app/PostureEstimation.h"
#include "app/LineMonitor.h"
#include "util/PID.h"

class GarageLApproachState : public ControlState {
	typedef ControlState base;

public:
	GarageLApproachState();
	virtual ~GarageLApproachState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	BalancingWalker* balancingWalker;
	Tail* tail;
	PID* pidTurn;
	LineMonitor* lineMonitor;

};

#endif  // NXT_CONTROL_STATE_GARAGELAPPROACHSTATE_H_
