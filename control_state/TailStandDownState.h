/******************************************************************************
 *  TailStandDownState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  Definition of the Class TailStandDownState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_TAILSTANDDOWNSTATE_H_
#define NXT_CONTROL_STATE_TAILSTANDDOWNSTATE_H_

#include "control_state/ControlState.h"
#include "app/Tail.h"
#include "unit/balancingWalker.h"

class TailStandDownState : public ControlState {
public:
	TailStandDownState();
	virtual ~TailStandDownState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	Tail* tail;
	BalancingWalker* balancingWalker;

};

#endif  // NXT_CONTROL_STATE_TAILSTANDDOWNSTATE_H_
