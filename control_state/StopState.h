/******************************************************************************
 *  StopState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  Definition of the Class StopState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_STOPSTATE_H_
#define NXT_CONTROL_STATE_STOPSTATE_H_

#include "control_state/ControlState.h"

class StopState : public ControlState {
public:
	StopState();
	virtual ~StopState();

	// override
	virtual void execute();
	virtual ControlState* next();
};

#endif  // NXT_CONTROL_STATE_STOPSTATE_H_
