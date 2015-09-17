/******************************************************************************
 *  CalibrationWhiteState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/15
 *  Definition of the Class CalibrationWhiteState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_CALIBRATIONWHITESTATE_H_
#define NXT_CONTROL_STATE_CALIBRATIONWHITESTATE_H_

#include "control_state/ControlState.h"
#include "app/Tail.h"
#include "app/UIManager.h"
#include "app/LineMonitor.h"
#include "unit/balancingWalker.h"

class CalibrationWhiteState : public ControlState {
	typedef ControlState base;

public:
	CalibrationWhiteState();
	virtual ~CalibrationWhiteState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	Tail* tail;
	BalancingWalker* balancingWalker;
	UIManager* uiManager;
	LineMonitor* lineMonitor;

};

#endif  // NXT_CONTROL_STATE_CALIBRATIONWHITESTATE_H_
