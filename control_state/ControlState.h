/******************************************************************************
 *  ControlState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  Definition of the Class ControlState
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_CONTROL_STATE_CONTROLSTATE_H_
#define NXT_CONTROL_STATE_CONTROLSTATE_H_

class ControlState {

public:
	ControlState(){};
	virtual ~ControlState(){};

	// 以下の関数を必ずオーバーライドする（RAMサイズの関係で？純粋仮想関数が使えない）
	virtual void execute(){};
	virtual ControlState* next(){return this;};

};

#endif  // NXT_CONTROL_STATE_CONTROLSTATE_H_
