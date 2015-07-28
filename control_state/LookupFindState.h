/******************************************************************************
 *  LookupFindState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  Definition of the Class LookupFindState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_LOOKUPFINDSTATE_H_
#define NXT_CONTROL_STATE_LOOKUPFINDSTATE_H_

#include "app/LineMonitor.h"
#include "app/Tail.h"
#include "control_state/ControlState.h"
#include "device/SonarSensor.h"
#include "unit/balancingWalker.h"
#include "util/PID.h"

class LookupFindState : public ControlState {
	typedef ControlState base;

public:
	LookupFindState();
	virtual ~LookupFindState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	Tail* tail;
	BalancingWalker* balancingWalker;
	SonarSensor* sonarSensor;
	LineMonitor* lineMonitor;
	PID* pidTurn;

	// execute(), next()

	// execute()

	// next()

	// その他

};

#endif  // NXT_CONTROL_STATE_LOOKUPFINDSTATE_H_
