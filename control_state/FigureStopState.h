/******************************************************************************
 *  FigureStopState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/23
 *  Definition of the Class FigureStopState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_FIGURESTOPSTATE_H_
#define NXT_CONTROL_STATE_FIGURESTOPSTATE_H_

#include "control_state/ControlState.h"
#include "unit/balancingWalker.h"
#include "app/Tail.h"
#include "app/PostureEstimation.h"
#include "util/PID.h"

class FigureStopState : public ControlState {
	typedef ControlState base;

public:
	FigureStopState();
	virtual ~FigureStopState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	BalancingWalker* balancingWalker;
	Tail* tail;
	PID* pidTurn;
	PostureEstimation* postureEstimation;

	double startDirection;

};

#endif  // NXT_CONTROL_STATE_FIGURESTOPSTATE_H_
