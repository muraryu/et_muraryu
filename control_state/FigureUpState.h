/******************************************************************************
 *  FigureUpState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/23
 *  Definition of the Class FigureUpState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_FIGUREUPSTATE_H_
#define NXT_CONTROL_STATE_FIGUREUPSTATE_H_

#include "control_state/ControlState.h"
#include "unit/balancingWalker.h"
#include "app/Tail.h"
#include "util/PID.h"

class FigureUpState : public ControlState {
	typedef ControlState base;

public:
	FigureUpState();
	virtual ~FigureUpState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	BalancingWalker* balancingWalker;
	Tail* tail;

	// execute(), next()

	// execute()

	// next()
	int startRightEnc;

};

#endif  // NXT_CONTROL_STATE_FIGUREUPSTATE_H_
