/******************************************************************************
 *  Driver.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  Definition of the Class Driver
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_UTIL_DRIVER_H_
#define NXT_UTIL_DRIVER_H_

#include "control_state/ControlState.h";

class Driver {

public:
	Driver::Driver(ControlState* controlState);
	virtual ~Driver();

	void execute();
	void setControlState(ControlState* controlState);

private:
	ControlState* controlState;
	ControlState* prevControlState;

};

#endif  // NXT_UTIL_DRIVER_H_
