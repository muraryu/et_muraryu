/******************************************************************************
 *  Tail.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/09
 *  Definition of the Class Tail
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_APP_TAIL_H_
#define NXT_APP_TAIL_H_

#include "util/PID.h"
#include "app/Tail.h"

class Tail {
public:
	static Tail* getInstance();
	void control();
	void setCommandAngle(int angle);	// セッター
	int getAngle();

private:
	Tail();
	~Tail();

	static bool insFlag;
	static Tail* instance;
	int commandAngle;			// しっぽ目標角度
	PID* pid;					// PIDコントローラ


};

#endif  // NXT_APP_TAIL_H_
