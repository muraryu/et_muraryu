/******************************************************************************
 *  FigureFindLineState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/24
 *  Definition of the Class FigureFindLineState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_FIGUREFINDLINESTATE_H_
#define NXT_CONTROL_STATE_FIGUREFINDLINESTATE_H_

#include "control_state/ControlState.h"

#include "unit/balancingWalker.h"
#include "app/PostureEstimation.h"
#include "app/LineMonitor.h"

class FigureFindLineState : public ControlState {
	typedef ControlState base;

public:
	FigureFindLineState();
	virtual ~FigureFindLineState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	BalancingWalker* balancingWalker;
	PostureEstimation* postureEstimation;
	LineMonitor* lineMonitor;

	// execute(), next()
	bool findFlag;

	// execute()
	double minBrightness;

	// next()
	double startDirection;

	// その他

};

#endif  // NXT_CONTROL_STATE_FIGUREFINDLINESTATE_H_
