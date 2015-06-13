/******************************************************************************
 *  TailStandDownState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  Definition of the Class TailStandDownState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_TAILSTANDDOWNSTATE_H_
#define NXT_CONTROL_STATE_TAILSTANDDOWNSTATE_H_

#include "control_state/ControlState.h"
#include "app/Tail.h"
#include "unit/balancingWalker.h"
#include "util/Time.h"

class TailStandDownState : public ControlState {
	typedef ControlState base;

public:
	TailStandDownState();
	virtual ~TailStandDownState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	Tail* tail;
	BalancingWalker* balancingWalker;
	Time* time;

	// execute(), next()

	// execute()
	double commandAngle1;
	bool flag1;
	double startTime1;
	int satValue1;

	// next()
	double startTime2;
	int satValue2;

};

#endif  // NXT_CONTROL_STATE_TAILSTANDDOWNSTATE_H_
