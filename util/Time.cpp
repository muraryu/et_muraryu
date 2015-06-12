/******************************************************************************
 *  Time.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/09
 *  時刻
 *  シングルトン
 *  Author: muraryu
 *****************************************************************************/

#include "Time.h"

#include "util/Bluetooth.h"

bool Time::insFlag = false;
Time* Time::instance;

/**
 * コンストラクタ
 */
Time::Time()
{
	// メンバ初期化
	this->time = 0;
}

/**
 * インスタンス取得
 */
Time* Time::getInstance() {
	if(insFlag == false){
		Time::instance = new Time();
		insFlag = true;
	}
	return Time::instance;
}

/**
 * 時刻取得
 */
double Time::getTime() {
	return this->time;
}

/**
 * 時刻を進める
 */
void Time::forward() {
	this->time += 0.004;
}
