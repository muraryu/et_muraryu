/******************************************************************************
 *  FigureStandUpState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  Definition of the Class FigureStandUpState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_FIGURESTANDUPSTATE_H_
#define NXT_CONTROL_STATE_FIGURESTANDUPSTATE_H_

#include "control_state/ControlState.h"
#include "app/Tail.h"
#include "app/LineMonitor.h"
#include "unit/balancingWalker.h"
#include "util/Time.h"
#include "util/PID.h"

class FigureStandUpState : public ControlState {
	typedef ControlState base;

public:
	FigureStandUpState();
	virtual ~FigureStandUpState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	Tail* tail;
	Time* time;
	BalancingWalker* balancingWalker;
	LineMonitor* lineMonitor;

	// execute(), next()
	double startTime;

	// execute()
	int referenceEncValue;

	// next()

	// その他
	PID* pid;

};

#endif  // NXT_CONTROL_STATE_FIGURESTANDUPSTATE_H_
