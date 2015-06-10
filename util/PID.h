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
	PID(double p, double i, double d);
	virtual ~PID();

	double calc(double r, double y);
	void setP(double p);
	void setI(double i);
	void setD(double d);

private:
	double p;			// 比例パラメータ
	double i;			// 積分パラメータ
	double d;			// 微分パラメータ
	double sumError;	// 誤差積分
	double prevE;		// 前回入力値

};

#endif  // NXT_UTIL_PID_H_
