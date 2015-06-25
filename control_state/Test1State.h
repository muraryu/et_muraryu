/******************************************************************************
 *  StopState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/05
 *  Definition of the Class Test1State
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_TEST1STATE_H_
#define NXT_CONTROL_STATE_TEST1STATE_H_

#include "ControlState.h"
#include "app/Tail.h"
#include "unit/BalancingWalker.h"
#include "util/PID.h"
#include "app/LineMonitor.h"
#include "util/Time.h"

class Test1State: public ControlState {
	typedef ControlState base;

public:
	Test1State();
	virtual ~Test1State();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	Tail* tail;
	BalancingWalker* balancingWalker;
	LineMonitor* lineMonitor;
	PID* pid;

	// execute(), next()

	// execute()

	// next()
	Time* time;
	double startTime;
};

#endif /* NXT_CONTROL_STATE_TEST1STATE_H_ */
