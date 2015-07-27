/******************************************************************************
 *  CalibrationBlackState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/15
 *  Definition of the Class CalibrationBlackState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_CALIBRATIONBLACKSTATE_H_
#define NXT_CONTROL_STATE_CALIBRATIONBLACKSTATE_H_

#include "control_state/ControlState.h"
#include "app/UIManager.h"
#include "app/LineMonitor.h"
#include "app/Tail.h"

class CalibrationBlackState : public ControlState {
	typedef ControlState base;

public:
	CalibrationBlackState();
	virtual ~CalibrationBlackState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	UIManager* uiManager;
	LineMonitor* lineMonitor;
	Tail* tail;

	// execute(), next()

	// execute()

	// next()

};

#endif  // NXT_CONTROL_STATE_CALIBRATIONBLACKSTATE_H_
