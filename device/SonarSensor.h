/******************************************************************************
 *  ControlState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  Definition of the Class SonarSensor
 *  Author: muraryu
 *****************************************************************************/

#ifndef SONARSENSOR_H_
#define SONARSENSOR_H_

#include "Port.h"

namespace ecrobot
{

class SonarSensor
{
public:
	SonarSensor(ePortS port);	// コンストラクタ
	virtual ~SonarSensor();		// デストラクタ		計測を終了する

	long getValue();			// 距離センサ値を取得 0~255

private:
	ePortS port;

};

}

#endif
