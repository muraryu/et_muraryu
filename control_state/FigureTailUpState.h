/******************************************************************************
 *  FigureTailUpState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/23
 *  Definition of the Class FigureTailUpState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_FIGURETAILUPSTATE_H_
#define NXT_CONTROL_STATE_FIGURETAILUPSTATE_H_

#include "control_state/ControlState.h"
#include "unit/balancingWalker.h"
#include "app/Tail.h"
#include "util/Time.h"

class FigureTailUpState : public ControlState {
	typedef ControlState base;

public:
	FigureTailUpState();
	virtual ~FigureTailUpState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	BalancingWalker* balancingWalker;
	Tail* tail;
	Time* time;

	double startTime;		// 開始時の時刻
	int startRightEnc;		// 開始時の右車輪角度

};

#endif  // NXT_CONTROL_STATE_FIGURETAILUPSTATE_H_
