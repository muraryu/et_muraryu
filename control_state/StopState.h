/******************************************************************************
 *  StopState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  Definition of the Class StopState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_UTIL_STOPSTATE_H_
#define NXT_UTIL_STOPSTATE_H_

#include "control_state/ControlState.h";

class StopState : public ControlState {

public:
	StopState::StopState();
	virtual ~StopState();

	virtual ControlState* execute();
};

#endif  // NXT_UTIL_STOPSTATE_H_
