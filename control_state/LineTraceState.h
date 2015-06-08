/******************************************************************************
 *  StopState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/05
 *  Definition of the Class LineTraceState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_LINETRACESTATE_H_
#define NXT_CONTROL_STATE_LINETRACESTATE_H_

#include "ControlState.h"

class LineTraceState: public ControlState {
public:
	LineTraceState();
	virtual ~LineTraceState();

	// override
	virtual void execute() = 0;
	virtual ControlState* next() = 0;
};

#endif /* NXT_CONTROL_STATE_LINETRACESTATE_H_ */
