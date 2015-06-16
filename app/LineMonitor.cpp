/******************************************************************************
 *  LineMonitor.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/02/07
 *  Implementation of the Class Balancer
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/


#include "LineMonitor.h"

#include "util/Bluetooth.h"

bool LineMonitor::insFlag = false;
LineMonitor* LineMonitor::instance;

/**
 * コンストラクタ
 */
LineMonitor::LineMonitor() {
	// メンバ初期化
	this->brightness = 0;
	this->brightnessBottom = 0;
	this->maimaiCount = 0;
}

/**
 * デストラクタ
 */
LineMonitor::~LineMonitor() {
}

/**
 * インスタンス取得
 */
LineMonitor* LineMonitor::getInstance() {
	if(insFlag == false){
		LineMonitor::instance = new LineMonitor();
		insFlag = true;
	}
	return LineMonitor::instance;
}

/**
 * インスタンス初期化
 */
void LineMonitor::init(ecrobot::LightSensor* lightSensor) {

	/* メンバ初期化 */
	this->lightSensor = lightSensor;

	/* 初期処理 */
	//
	ecrobot_set_light_sensor_active(NXT_PORT_S3);

}

/**
 * まいまい式による光強度取得
 * 0～1で正規化済み
 */
double LineMonitor::getBrightness() {

	return this->brightness;
	//return this->lightSensor->getBrightness();
}

/**
 * まいまい式
 * LEDオンオフ切替とセンサ値更新を行う
 */
void LineMonitor::maimai() {

	if(this->maimaiCount == 3) {		// LEDオン操作 センサ値最小値(外光)取得
		//Bluetooth::dataLogger(this->lightSensor->getBrightness()/10,4);
		this->brightnessBottom = (double)this->lightSensor->getBrightness()/1000;
		ecrobot_set_light_sensor_active(NXT_PORT_S3);
	}
	else if(this->maimaiCount == 6){	// LEDオフ操作 センサ値最大値(外光＋LED光)取得
		//Bluetooth::dataLogger(this->lightSensor->getBrightness()/10,8);
		this->brightness = (double)this->lightSensor->getBrightness()/1000 - this->brightnessBottom;
		ecrobot_set_light_sensor_inactive(NXT_PORT_S3);
		this->maimaiCount = 0;
	}
	else {
		//Bluetooth::dataLogger(this->lightSensor->getBrightness()/10,0);
	}
	this->maimaiCount++;
}
