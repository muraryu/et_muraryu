/******************************************************************************
 *  FigureDownState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/24
 *  Definition of the Class FigureDownState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_FIGUREDOWNSTATE_H_
#define NXT_CONTROL_STATE_FIGUREDOWNSTATE_H_

#include "control_state/ControlState.h"
#include "unit/balancingWalker.h"
#include "app/LineMonitor.h"
#include "util/PID.h"

class FigureDownState : public ControlState {
	typedef ControlState base;

public:
	FigureDownState();
	virtual ~FigureDownState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	BalancingWalker* balancingWalker;
	PID* pid;
	LineMonitor*lineMonitor;

	// execute(), next()

	// execute()

	// next()

};

#endif  // NXT_CONTROL_STATE_FIGUREDOWNSTATE_H_
