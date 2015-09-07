/******************************************************************************
 *  GarageSitForwardState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/23
 *  Definition of the Class GarageSitForwardState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_GARAGESITFORWARDSTATE_H_
#define NXT_CONTROL_STATE_GARAGESITFORWARDSTATE_H_

#include "control_state/ControlState.h"
#include "unit/balancingWalker.h"
#include "app/Tail.h"
#include "app/PostureEstimation.h"

class GarageSitForwardState : public ControlState {
	typedef ControlState base;

public:
	GarageSitForwardState();
	virtual ~GarageSitForwardState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	BalancingWalker* balancingWalker;
	Tail* tail;
	PostureEstimation* postureEstimation;
	PID* pidTurn;

	double startDirection;

};

#endif  // NXT_CONTROL_STATE_GARAGESITFORWARDSTATE_H_
