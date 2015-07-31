/******************************************************************************
 *  QuickStartState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  Definition of the Class QuickStartState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_QUICKSTARTSTATE_H_
#define NXT_CONTROL_STATE_QUICKSTARTSTATE_H_

#include "control_state/ControlState.h"
#include "app/Tail.h"
#include "unit/balancingWalker.h"

class QuickStartState : public ControlState {
	typedef ControlState base;

public:
	QuickStartState();
	virtual ~QuickStartState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	Tail* tail;
	BalancingWalker* balancingWalker;

	double angle;

};

#endif  // NXT_CONTROL_STATE_QUICKSTARTSTATE_H_
