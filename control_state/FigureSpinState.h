/******************************************************************************
 *  FigureSpinState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/24
 *  Definition of the Class FigureSpinState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_FIGURESPINSTATE_H_
#define NXT_CONTROL_STATE_FIGURESPINSTATE_H_

#include "control_state/ControlState.h"

#include "unit/balancingWalker.h"
#include "app/PostureEstimation.h"

class FigureSpinState : public ControlState {
	typedef ControlState base;

public:
	FigureSpinState();
	virtual ~FigureSpinState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	BalancingWalker* balancingWalker;
	PostureEstimation* postureEstimation;

	// execute(), next()

	// execute()

	// next()
	double startDirection;

	// その他

};

#endif  // NXT_CONTROL_STATE_FIGURESPINSTATE_H_
