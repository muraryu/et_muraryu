/******************************************************************************
 *  ReadyState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/15
 *  Definition of the Class ReadyState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_READYSTATE_H_
#define NXT_CONTROL_STATE_READYSTATE_H_

#include "control_state/ControlState.h"
#include "app/Tail.h"
#include "unit/balancingWalker.h"

class ReadyState : public ControlState {
	typedef ControlState base;

public:
	ReadyState();
	virtual ~ReadyState();

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

#endif  // NXT_CONTROL_STATE_READYSTATE_H_
