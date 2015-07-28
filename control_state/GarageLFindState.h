/******************************************************************************
 *  GarageLFindState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/07/28
 *  Definition of the Class GarageLFindState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_GARAGELFINDSTATE_H_
#define NXT_CONTROL_STATE_GARAGELFINDSTATE_H_

#include "control_state/ControlState.h"
#include "unit/balancingWalker.h"
#include "app/Tail.h"
#include "app/PostureEstimation.h"
#include "app/LineMonitor.h"
#include "util/PID.h"

class GarageLFindState : public ControlState {
	typedef ControlState base;

public:
	GarageLFindState();
	virtual ~GarageLFindState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	BalancingWalker* balancingWalker;
	Tail* tail;
	PID* pidTurn;
	PostureEstimation* postureEstimation;
	LineMonitor* lineMonitor;

	double startDirection;
	int startRightEnc;
	int figureEndRightEnc;
	bool figureEndFlag;

};

#endif  // NXT_CONTROL_STATE_GARAGELFINDSTATE_H_
