/******************************************************************************
 *  FigureBackState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/23
 *  Definition of the Class FigureBackState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_FIGUREBACKSTATE_H_
#define NXT_CONTROL_STATE_FIGUREBACKSTATE_H_

#include "control_state/ControlState.h"
#include "unit/balancingWalker.h"
#include "app/Tail.h"
#include "app/PostureEstimation.h"
#include "util/PID.h"

class FigureBackState : public ControlState {
	typedef ControlState base;

public:
	FigureBackState();
	virtual ~FigureBackState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	BalancingWalker* balancingWalker;
	Tail* tail;
	PostureEstimation* postureEstimation;
	PID* pidTurn;

	int startRightEnc;
	double startDirection;

};

#endif  // NXT_CONTROL_STATE_FIGUREBACKSTATE_H_
