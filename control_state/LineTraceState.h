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
	typedef ControlState base;

public:
	LineTraceState();
	virtual ~LineTraceState();

	// override
	virtual void execute();
	virtual ControlState* next();
};

#endif /* NXT_CONTROL_STATE_LINETRACESTATE_H_ */
