/******************************************************************************
 *  TailStandUpState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/12
 *  Definition of the Class TailStandUpState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_TAILSTANDUPSTATE_H_
#define NXT_CONTROL_STATE_TAILSTANDUPSTATE_H_

#include "control_state/ControlState.h"
#include "app/Tail.h"
#include "unit/balancingWalker.h"

class TailStandUpState : public ControlState {
public:
	TailStandUpState();
	virtual ~TailStandUpState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	Tail* tail;
	BalancingWalker* balancingWalker;

};

#endif  // NXT_CONTROL_STATE_TAILSTANDUPSTATE_H_
