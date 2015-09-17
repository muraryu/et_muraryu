/******************************************************************************
 *  StopState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/07/01
 *  Definition of the Class FigureLineTraceState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_FIGURELINETRACESTATE_H_
#define NXT_CONTROL_STATE_FIGURELINETRACESTATE_H_

#include "ControlState.h"
#include "unit/BalancingWalker.h"
#include "app/Tail.h"
#include "util/PID.h"
#include "util/Time.h"
#include "app/LineMonitor.h"
#include "app/PostureEstimation.h"

class FigureLineTraceState: public ControlState {
	typedef ControlState base;

public:
	FigureLineTraceState();
	virtual ~FigureLineTraceState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	BalancingWalker* balancingWalker;
	Tail* tail;
	LineMonitor* lineMonitor;
	Time* time;
	PID* pidForward;
	PID* pidTurn;
	PostureEstimation* postureEstimation;

	int startRightEnc;
	double startDirection;
	double startTime;
	double stableTime;

};

#endif /* NXT_CONTROL_STATE_FIGURELINETRACESTATE_H_ */
