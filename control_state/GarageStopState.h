/******************************************************************************
 *  GarageStopState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/23
 *  Definition of the Class GarageStopState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_GARAGESTOPSTATE_H_
#define NXT_CONTROL_STATE_GARAGESTOPSTATE_H_

#include "control_state/ControlState.h"
#include "unit/balancingWalker.h"
#include "util/time.h"
#include "app/Tail.h"

class GarageStopState : public ControlState {
	typedef ControlState base;

public:
	GarageStopState();
	virtual ~GarageStopState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	BalancingWalker* balancingWalker;
	Tail* tail;
	Time* time;

	double startTime;


};

#endif  // NXT_CONTROL_STATE_GARAGESTOPSTATE_H_
