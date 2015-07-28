/******************************************************************************
 *  LookupStandUpState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/12
 *  Definition of the Class LookupStandUpState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_LOOKUPSTANDUPSTATE_H_
#define NXT_CONTROL_STATE_LOOKUPSTANDUPSTATE_H_

#include "control_state/ControlState.h"
#include "app/Tail.h"
#include "unit/balancingWalker.h"

class LookupStandUpState : public ControlState {
	typedef ControlState base;

public:
	LookupStandUpState();
	virtual ~LookupStandUpState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	Tail* tail;
	BalancingWalker* balancingWalker;

	// execute(), next()

	// execute()

	// next()

};

#endif  // NXT_CONTROL_STATE_LOOKUPSTANDUPSTATE_H_
