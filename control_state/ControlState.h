/******************************************************************************
 *  ControlState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  Definition of the Class ControlState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_UTIL_CONTROLSTATE_H_
#define NXT_UTIL_CONTROLSTATE_H_

class ControlState {

public:
	ControlState();
	virtual ~ControlState();

	virtual void execute() = 0;
	virtual ControlState* next() = 0;

};

#endif  // NXT_UTIL_CONTROLSTATE_H_
