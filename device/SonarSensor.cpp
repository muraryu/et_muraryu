/******************************************************************************
 *  FigureDownState.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/07/23
 *  超音波センサ
 *  シングルトン
 *  init()で初期化時に計測開始
 *  Author: muraryu
 *****************************************************************************/

#include "SonarSensor.h"

extern "C" {
#include "ecrobot_interface.h"
}

using namespace ecrobot;

bool SonarSensor::insFlag = false;
SonarSensor* SonarSensor::instance;

/**
 * コンストラクタ
 * @param port	ポート番号
 */
SonarSensor::SonarSensor() {
}

/**
 * デストラクタ
 */
SonarSensor::~SonarSensor() {

	// 超音波センサ測定停止
	ecrobot_term_sonar_sensor(this->port);
}

/**
 * インスタンス取得
 */
SonarSensor* SonarSensor::getInstance() {
	if (insFlag == false) {
		SonarSensor::instance = new SonarSensor();
		insFlag = true;
	}
	return SonarSensor::instance;
}

/**
 * インスタンス初期化
 */
void SonarSensor::init(ePortS port) {

	/* メンバ初期化 */
	this->port = port;

	/* 初期処理 */
	// 超音波センサ測定開始
	ecrobot_init_sonar_sensor(this->port);

}

/**
 * 超音波センサから距離を取得
 * @return	距離
 */
long SonarSensor::getValue() {
	return ecrobot_get_sonar_sensor(this->port);
}
