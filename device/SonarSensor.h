/******************************************************************************
 *  ControlState.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/03
 *  Definition of the Class SonarSensor
 *  Author: muraryu
 *****************************************************************************/

#ifndef SONARSENSOR_H_
#define SONARSENSOR_H_

#include "Port.h"

class SonarSensor
{
public:
	static SonarSensor* getInstance();
	void init(ePortS por);

    // シングルトンパターン
	static bool insFlag;				// シングルトンインスタンス生成フラグ(生成前=false, 生成後=true)
	static SonarSensor* instance;		// シングルトンインスタンス

	int getValue();			// 距離センサ値を取得 0~255

private:
	ePortS port;

	SonarSensor();	// コンストラクタ
	virtual ~SonarSensor();		// デストラクタ		計測を終了する

};

#endif
