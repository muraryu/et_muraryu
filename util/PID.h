/******************************************************************************
 *  PID.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/02
 *  Definition of the Class Balancer
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_UTIL_PID_H_
#define NXT_UTIL_PID_H_

class PID {

public:
	PID(U16 p, U16 i, U16 d, S32 initU);
	virtual ~PID();

	S32 calc(S32 r, S32 u);
	void setP(U32 p);
	void setI(U32 i);
	void setD(U32 d);

private:
	U16 p;			// 比例パラメータ
	U16 i;			// 積分パラメータ
	U16 d;			// 微分パラメータ
	S32 sumError;	// 誤差積分
	S32 prevU;		// 前回入力値

};

#endif  // NXT_UTIL_PID_H_
