/******************************************************************************
 *  Line.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/07/13
 *  ライン情報
 *  Author: muraryu
 *****************************************************************************/

#include "Line.h"

/**
 * コンストラクタ
 * @param brightnessTop		ライン上の輝度
 * @param brightnessBottom	ライン外の輝度
 */
Line::Line(double brightnessTop, double brightnessBottom) {
	this->brightnessTop = brightnessTop;
	this->brightnessBottom = brightnessBottom;
}

/**
 * デストラクタ
 */
Line::~Line() {
}

void Line::setBrightnessBottom(double brightnessBottom) {
	this->brightnessBottom = brightnessBottom;
}

void Line::setBrightnessTop(double brightnessTop) {
	this->brightnessTop = brightnessTop;
}

double Line::getBrightnessTop() {
	return this->brightnessTop;
}

double Line::getBrightnessBottom() {
	return this->brightnessBottom;
}
