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
#include "unit/balancingWalker.h"
#include "util/Time.h"

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

	// execute(), next()

	// execute()

	// next()
	double startTime;

};

#endif  // NXT_CONTROL_STATE_LOOKUPPASSSTATE_H_
