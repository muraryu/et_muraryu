/******************************************************************************
 *  GarageSitDownState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  Definition of the Class GarageSitDownState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_GARAGESITDOWNSTATE_H_
#define NXT_CONTROL_STATE_GARAGESITDOWNSTATE_H_

#include "control_state/ControlState.h"
#include "app/Tail.h"
#include "app/LineMonitor.h"
#include "unit/balancingWalker.h"
#include "util/Time.h"
#include "util/PID.h"

class GarageSitDownState : public ControlState {
	typedef ControlState base;

public:
	GarageSitDownState();
	virtual ~GarageSitDownState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	Tail* tail;
	Time* time;
	BalancingWalker* balancingWalker;
	LineMonitor* lineMonitor;

	double startTime;
	int referenceEncValue;

};

#endif  // NXT_CONTROL_STATE_GARAGESITDOWNSTATE_H_
