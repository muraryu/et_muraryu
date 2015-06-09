/******************************************************************************
 *  Tail.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/09
 *  Definition of the Class Tail
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_APP_TAIL_H_
#define NXT_APP_TAIL_H_

class Tail {
public:
	static Tail* getInstance();
	void setAngle(int angle);	// セッター

private:
	Tail();
	int angle;					// しっぽ目標角度

};

#endif  // NXT_APP_TAIL_H_
