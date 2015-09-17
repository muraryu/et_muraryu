/******************************************************************************
 *  FigureSitDownState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  Definition of the Class FigureSitDownState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_FIGURESITDOWNSTATE_H_
#define NXT_CONTROL_STATE_FIGURESITDOWNSTATE_H_

#include "control_state/ControlState.h"
#include "app/Tail.h"
#include "app/LineMonitor.h"
#include "unit/balancingWalker.h"
#include "util/Time.h"
#include "util/PID.h"

class FigureSitDownState : public ControlState {
	typedef ControlState base;

public:
	FigureSitDownState();
	virtual ~FigureSitDownState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	Tail* tail;
	Time* time;
	BalancingWalker* balancingWalker;
	LineMonitor* lineMonitor;
	PID* pid;

	double startTime;
	int referenceEncValue;

};

#endif  // NXT_CONTROL_STATE_FIGURESITDOWNSTATE_H_
