/******************************************************************************
 *  FigureDownState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/07/23
 *  超音波センサ
 *  コンストラクタとデストラクタを呼ぶときに計測開始終了しているため注意
 *  Author: muraryu
 *****************************************************************************/

#include "SonarSensor.h"

extern "C" {
#include "ecrobot_interface.h"
}

using namespace ecrobot;


/**
 * コンストラクタ
 * @param port	ポート番号
 */
SonarSensor::SonarSensor(ePortS port) {
	this->port = port;

	// 超音波センサ初期化
	ecrobot_init_sonar_sensor(this->port);
}

/**
 * デストラクタ
 */
SonarSensor::~SonarSensor() {
	// 超音波センサ測定停止
	ecrobot_term_sonar_sensor(this->port);
}

/**
 * 超音波センサから距離を取得
 * @return	距離
 */
long SonarSensor::getValue() {
	return ecrobot_get_sonar_sensor(this->port);
}
