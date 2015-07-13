/******************************************************************************
 *  StopState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/05
 *  Definition of the Class LineTraceFindGrayState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_LINETRACEFINDGRAYSTATE_H_
#define NXT_CONTROL_STATE_LINETRACEFINDGRAYSTATE_H_

#include "ControlState.h"
#include "app/Tail.h"
#include "unit/BalancingWalker.h"
#include "util/PID.h"
#include "app/LineMonitor.h"

class LineTraceFindGrayState: public ControlState {
	typedef ControlState base;

public:
	LineTraceFindGrayState();
	virtual ~LineTraceFindGrayState();

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
};

#endif /* NXT_CONTROL_STATE_LINETRACEFINDGRAYSTATE_H_ */
