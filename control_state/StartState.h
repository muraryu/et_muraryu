/******************************************************************************
 *  QuickStartState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  Definition of the Class QuickStartState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_STARTSTATE_H_
#define NXT_CONTROL_STATE_STARTSTATE_H_

#include "control_state/ControlState.h"
#include "app/Tail.h"
#include "unit/balancingWalker.h"

class StartState : public ControlState {
	typedef ControlState base;

public:
	StartState();
	virtual ~StartState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	Tail* tail;
	BalancingWalker* balancingWalker;

	double angle;

};

#endif  // NXT_CONTROL_STATE_STARTSTATE_H_
