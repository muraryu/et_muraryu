/******************************************************************************
 *  LineMonitor.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/02/07
 *  Definition of the Class LineMonitor
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef NXT_UNIT_LINEMONITOR_H_
#define NXT_UNIT_LINEMONITOR_H_

#include "LightSensor.h"

// 定義
class LineMonitor {
public:
	static LineMonitor* getInstance();
	void init(ecrobot::LightSensor* lightSensor);
    double getBrightness();
    void maimai();

private:
    LineMonitor();
    virtual ~LineMonitor();

	static bool insFlag;				// シングルトンインスタンス生成フラグ(生成前=false, 生成後=true)
	static LineMonitor* instance;		// シングルトンインスタンス

    ecrobot::LightSensor* lightSensor;	// 光センサ
    double brightness;						// 光センサ値
    double brightnessBottom;				// 光センサ値 まいまい式用 外光のみの反射光
    short maimaiCount;					// まいまい式用カウンタ
};

#endif  // NXT_UNIT_LINEMONITOR_H_
