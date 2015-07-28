/******************************************************************************
 *  LookupSitDownState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  Definition of the Class LookupSitDownState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_LOOKUPSITDOWNSTATE_H_
#define NXT_CONTROL_STATE_LOOKUPSITDOWNSTATE_H_

#include "control_state/ControlState.h"
#include "app/Tail.h"
#include "unit/balancingWalker.h"

class LookupSitDownState : public ControlState {
	typedef ControlState base;

public:
	LookupSitDownState();
	virtual ~LookupSitDownState();

	// override
	virtual void execute();
	virtual ControlState* next();

private:
	Tail* tail;
	BalancingWalker* balancingWalker;

};

#endif  // NXT_CONTROL_STATE_LOOKUPSITDOWNSTATE_H_
