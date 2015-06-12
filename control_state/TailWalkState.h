/******************************************************************************
 *  TailWalkState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  Definition of the Class TailWalkState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_TAILWALKSTATE_H_
#define NXT_CONTROL_STATE_TAILWALKSTATE_H_

#include "control_state/ControlState.h"
#include "app/Tail.h"
#include "unit/balancingWalker.h"
#include "util/Time.h"

class TailWalkState : public ControlState {
public:
	TailWalkState();
	virtual ~TailWalkState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	BalancingWalker* balancingWalker;
	Time* time;
	double startTime;

};

#endif  // NXT_CONTROL_STATE_TAILWALKSTATE_H_
