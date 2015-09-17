/******************************************************************************
 *  StopState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/24
 *  Definition of the Class FigureFindState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_FIGUREFINDSTATE_H_
#define NXT_CONTROL_STATE_FIGUREFINDSTATE_H_

#include "ControlState.h"
#include "unit/BalancingWalker.h"
#include "util/PID.h"
#include "app/LineMonitor.h"

class FigureFindState: public ControlState {
	typedef ControlState base;

public:
	FigureFindState();
	virtual ~FigureFindState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	BalancingWalker* balancingWalker;
	LineMonitor* lineMonitor;
	PID* pid;

};

#endif /* NXT_CONTROL_STATE_FIGUREFINDSTATE_H_ */
