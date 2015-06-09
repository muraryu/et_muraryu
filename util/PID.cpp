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
 * @param initE
 */
PID::PID(U16 p, U16 i, U16 d) {
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
S32 PID::calc(S32 r, S32 y) {

	S32 u;		// 操作量
	S32 e;		// 偏差
	S32 diff;	// 微分係数

	// 偏差計算
	e = r - y;

	// 偏差積分値更新
	this->sumError += e;

	// 微分係数計算・更新
	diff = e - this->prevE;
	this->prevE = e;

	// PID出力計算
	y = this->p * e + this->i * this->sumError + this->d * diff;

	return y;

}

void PID::setP(U32 p) {
	this->p = p;
}

void PID::setI(U32 i) {
	this->i = i;
}

void PID::setD(U32 d) {
	this->d = d;
}
