/******************************************************************************
 *  StopState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  Definition of the Class StopState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_STOPSTATE_H_
#define NXT_CONTROL_STATE_STOPSTATE_H_

#include "control_state/ControlState.h"
#include "app/Tail.h"
#include "unit/balancingWalker.h"
#include "util/Time.h"
#include "util/PID.h"

class StopState : public ControlState {
	typedef ControlState base;

public:
	StopState();
	virtual ~StopState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	Tail* tail;
	Time* time;
	BalancingWalker* balancingWalker;

	// execute(), next()
	double startTime;

	// execute()
	int referenceEncValue;

	// next()

	// その他
	PID* pid;

};

#endif  // NXT_CONTROL_STATE_STOPSTATE_H_
