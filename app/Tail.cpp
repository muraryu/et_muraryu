/******************************************************************************
 *  Tail.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/09
 *  しっぽ
 *  Author: muraryu
 *****************************************************************************/

#include "Tail.h"

bool Tail::insFlag = false;
Tail* Tail::instance;

/**
 * コンストラクタ
 */
Tail::Tail()
{
	// メンバ初期化
	this->pid = new PID(1,1,1);
	this->commandAngle = 0;
}

/**
 * インスタンス取得
 */
Tail* Tail::getInstance() {
	if(insFlag == false){
		Tail::instance = new Tail();
		insFlag = true;
	}
	return Tail::instance;
}

/**
 *
 */
void Tail::control() {

	double pwm = this->pid->calc(this->commandAngle, this->getAngle());

}

/**
 * セッター
 * @param angle	パラメータD
 */
void Tail::setCommandAngle(int angle) {
	this->commandAngle = angle;
}
