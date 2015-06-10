/******************************************************************************
 *  TailStandState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  Definition of the Class TailStandState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_TAILSTANDSTATE_H_
#define NXT_CONTROL_STATE_TAILSTANDSTATE_H_

#include "control_state/ControlState.h"
#include "app/Tail.h"
#include "unit/balancingWalker.h"

class TailStandState : public ControlState {
public:
	TailStandState();
	virtual ~TailStandState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	Tail* tail;
	BalancingWalker* balancingWalker;

};

#endif  // NXT_CONTROL_STATE_TAILSTANDSTATE_H_
