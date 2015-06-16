/******************************************************************************
 *  String.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/02
 *  Definition of the Class String
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_UTIL_STRING_H_
#define NXT_UTIL_STRING_H_

class Str {

public:
	static char* valueOf(int value);
//	static char* valueOf(unsigned int value);
//	static char* valueOf(short value);
//	static char* valueOf(unsigned short value);
	//static char* valueOf(double value);
//	static char* valueOf(float value);

private:
	Str(const char* str);
	virtual ~Str();


};

#endif  // NXT_UTIL_STRING_H_
