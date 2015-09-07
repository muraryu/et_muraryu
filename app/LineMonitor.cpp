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

	// ライン情報をプリセット値で生成
	this->normalLine = new Line(0.30, 0.10);
	this->grayLine = new Line(0.20, 0.12);
	this->figureLine = new Line(0.30, 0.10);

	// 現在のラインをノーマルラインに初期化
	this->currentLine = normalLine;

	// グレー検知
	this->lightStable = false;
	lightBufIndex = 0;
	lightStableCount = 0;
	for(int i=0; i<16; i++) {
		lightBuf[i] = 0;
	}
	grayFound = false;
	GrayFoundTime = Time::getInstance()->getTime();
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
	if (insFlag == false) {
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
 * まいまい式による輝度取得
 * 0～1で正規化済み
 */
double LineMonitor::getBrightness() {
	return this->brightness;
}

/**
 * 現在の正規化済み輝度を取得
 * ライン種類によりフィードバック制御に差が出るのを防ぐために制御計算で用いる
 */
double LineMonitor::getAdjustedBrightness() {
	return this->adjustBrightnessRange(this->brightness);
}

/**
 * まいまい式
 * LEDオンオフ切替、0～1に正規化した輝度更新を行う
 * この関数を周期的に呼び出すことでメンバ変数brightnessに最新の輝度が入るようになる
 */
void LineMonitor::maimai() {

	/*
	if (this->maimaiCount == 4) {		// LEDオン操作 センサ値最小値(外光)取得
		//Bluetooth::dataLogger(this->lightSensor->getBrightness()/10,4);
		//this->brightnessBottom = (double) this->lightSensor->getBrightness() / 1024;
		ecrobot_set_light_sensor_active(NXT_PORT_S3); //TODO 光センサクラスにやらせたほうがよさそう
	} else if (this->maimaiCount == 8) {	// LEDオフ操作 センサ値最大値(外光＋LED光)取得
		//Bluetooth::dataLogger(this->lightSensor->getBrightness()/10,8);
		//this->brightness = ((double) this->lightSensor->getBrightness() / 1024 - this->brightnessBottom);
		//this->brightness = this->brightness*0.6 + ((double) this->lightSensor->getBrightness() / 1024 - this->brightnessBottom)*0.4;
		ecrobot_set_light_sensor_inactive(NXT_PORT_S3); //TODO 光センサクラスにやらせたほうがよさそう
		this->maimaiCount = 0;
		//Bluetooth::dataLogger(this->getAdjustedBrightness()*100,this->getBrightness()*100);
	} else {
		//Bluetooth::dataLogger(this->lightSensor->getBrightness()/10,0);
	}
	this->maimaiCount++;
	*/
	this->brightness = (double) this->lightSensor->getBrightness() / 1024;
	//Bluetooth::sendMessage(this->brightness * 1000);

	// グレー検知
	lightBuf[lightBufIndex%16] = this->getAdjustedBrightness();
	double lightDiff = lightBuf[lightBufIndex%16] - lightBuf[(lightBufIndex+1)%16]; // 補正済み光センサ値変化速度
	if(lightStable == false && -0.03 <= lightDiff && lightDiff <= 0.03) { // 値が安定してからグレー検知開始
		lightStableCount++;
		if(500 < lightStableCount) {
			lightStable = true;
			//Bluetooth::sendMessage("Light Value Stable.\n", 21);
		}
	} else {
		lightStableCount = 0;
	}
	//Bluetooth::sendMessage((lightBuf[lightBufIndex%16] - lightBuf[(lightBufIndex+1)%16])*10000);
	if(1.0 < Time::getInstance()->getTime() - GrayFoundTime && lightStable == true && 0.05 < lightBuf[lightBufIndex%16] - lightBuf[(lightBufIndex+1)%16]) { //TODO 当日調整0.05 前回の検知から1秒経過＆値が安定してた＆変化速度が一定以上でグレー検知
		//Bluetooth::sendMessage("Gray Line Found.\n", 18);
		GrayFoundTime = Time::getInstance()->getTime();
		grayFound = true;
		lightStable = false;
	} else if(Time::getInstance()->getTime() - GrayFoundTime < 1.0) { // グレー見つけたら一秒間フラグを立てる
		//Bluetooth::sendMessage((lightBuf[lightBufIndex%16] - lightBuf[(lightBufIndex+1)%16])*10000);
		grayFound = true;
	} else { // グレー見つけてから1秒後にフラグおろす
		grayFound = false;
	}
	lightBufIndex = (lightBufIndex + 1) % 16;

}

/**
 * 白のキャリブレーション
 */
void LineMonitor::calibrateWhite() {
	double white = this->getBrightness();
	this->normalLine->setBrightnessTop(white);
	this->grayLine->setBrightnessTop(white);
	Bluetooth::sendMessage((int) (white * 100));
}

/**
 * 黒のキャリブレーション
 */
void LineMonitor::calibrateBlack() {
	double black = this->getBrightness();
	this->normalLine->setBrightnessBottom(black);
	this->grayLine->setBrightnessBottom(black);
	this->figureLine->setBrightnessBottom(black);
	Bluetooth::sendMessage((int) (black * 100));
}

/**
 * フィギュアLの白のキャリブレーション
 */
void LineMonitor::calibrateFigureWhite() {
	this->figureLine->setBrightnessTop(this->getBrightness());
	Bluetooth::sendMessage((int) (this->figureLine->getBrightnessTop() * 100));
}

/**
 * 現在のライン種別をノーマルラインに変更
 */
void LineMonitor::changeLineToNormal() {
	this->currentLine = this->normalLine;
}

/**
 * 現在のライン種別をグレーラインに変更
 */
void LineMonitor::changeLineToGray() {
	this->currentLine = this->grayLine;
}

/**
 * 現在のライン種別をラインに変更
 */
void LineMonitor::changeLineToFigure() {
	this->currentLine = this->figureLine;
}

/**
 * 走行中のラインのキャリブレーション上下幅で輝度を0～1の範囲に伸長して調整
 * @param brightness	輝度
 */
double LineMonitor::adjustBrightnessRange(double brightness) {

	double top = this->currentLine->getBrightnessTop();
	double bottom = this->currentLine->getBrightnessBottom();
	double adjustedBrightness = 0;

	// 割るゼロ回避
	if (top - bottom != 0) {
		adjustedBrightness = (brightness - bottom) / (top - bottom);
		// 範囲外になったら切り詰める
		if (adjustedBrightness < 0) {
			adjustedBrightness = 0;
		} else if (1 < adjustedBrightness) {
			adjustedBrightness = 1;
		}
	}

	return adjustedBrightness;
}

bool LineMonitor::getGrayFound() {
	return this->grayFound;
}
