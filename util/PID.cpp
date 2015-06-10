/******************************************************************************
 *  PID.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/02
 *  PID controlelr
 *  Author: muraryu
 *****************************************************************************/

extern "C" {
#include "ecrobot_interface.h"
}
#include "PID.h"

/**
 * コンストラクタ
 * PIDパラメータ、偏差積分値、初回入力値を初期化
 * @param p		パラメータP
 * @param i		パラメータI
 * @param d		パラメータD
 */
PID::PID(double p, double i, double d) {
	this->p = p;
	this->i = i;
	this->d = d;
	this->prevE = 0;
	this->sumError = 0;
}

/**
 * デストラクタ
 */
PID::~PID() {
}

/**
 * 目標値と制御量からPID計算を行い、操作量を返す
 * @param r 目標値
 * @param y 制御量
 */
double PID::calc(double r, double y) {

	double u;		// 操作量
	double e;		// 偏差
	double diff;	// 微分係数

	// 偏差計算
	e = r - y;

	// 偏差積分値更新
	this->sumError += e;

	// 微分係数計算・更新
	diff = e - this->prevE;
	this->prevE = e;

	// PID出力計算
	u = this->p * e + this->i * this->sumError + this->d * diff;

	return u;

}

void PID::setP(double p) {
	this->p = p;
}

void PID::setI(double i) {
	this->i = i;
}

void PID::setD(double d) {
	this->d = d;
}
