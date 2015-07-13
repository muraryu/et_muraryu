/******************************************************************************
 *  Line.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/07/13
 *  Definition of the Class Line
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_UTIL_LINE_H_
#define NXT_UTIL_LINE_H_

class Line {

public:
	Line(double brightnessTop, double brightnessBottom);
	virtual ~Line();

	void setBrightnessTop(double brightnessTop);
	void setBrightnessBottom(double brightnessTop);
	double getBrightnessTop();
	double getBrightnessBottom();


private:
	double brightnessTop;
	double brightnessBottom;

};

#endif  // NXT_UTIL_LINE_H_
