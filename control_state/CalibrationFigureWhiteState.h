/******************************************************************************
 *  CalibrationFigureWhiteState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/07/02
 *  Definition of the Class CalibrationFigureWhiteState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_CALIBRATIONFIGUREWHITESTATE_H_
#define NXT_CONTROL_STATE_CALIBRATIONFIGUREWHITESTATE_H_

#include "control_state/ControlState.h"
#include "app/UIManager.h"
#include "app/LineMonitor.h"
#include "app/Tail.h"

class CalibrationFigureWhiteState : public ControlState {
	typedef ControlState base;

public:
	CalibrationFigureWhiteState();
	virtual ~CalibrationFigureWhiteState();

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

#endif  // NXT_CONTROL_STATE_CALIBRATIONFIGUREWHITESTATE_H_
