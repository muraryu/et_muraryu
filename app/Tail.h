/******************************************************************************
 *  Tail.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/09
 *  Definition of the Class Tail
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_APP_TAIL_H_
#define NXT_APP_TAIL_H_

#include "Motor.h"

#include "util/PID.h"

class Tail {
public:
	static Tail* getInstance();
	void init(ecrobot::Motor* gTail);

	void control();
	void setCommandAngle(int angle);	// セッター
	S32 getAngle();
	double saturationTime();

private:
	Tail();
	~Tail();

	static bool insFlag;			// シングルトンインスタンス生成フラグ(生成前=false, 生成後=true)
	static Tail* instance;			// シングルトンインスタンス

	ecrobot::Motor* gTail;			// しっぽモーター
	int commandAngle;				// しっぽ目標角度
	PID* pid;						// PIDコントローラ

};

#endif  // NXT_APP_TAIL_H_
