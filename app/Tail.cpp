/******************************************************************************
 *  Tail.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/09
 *  しっぽ
 *  シングルトン
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
	this->pid = new PID(0,0.0001,0);
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
void Tail::init(ecrobot::Motor* gTail) {

	// モーター速度と角度を0に初期化
	gTail->reset();

	// メンバ初期化
	this->gTail = gTail;

}

/**
 * 目標角度に制御
 */
void Tail::control() {

	double pwm = this->pid->calc(this->commandAngle, this->getAngle(), -100, 100);
	gTail->setPWM((signed char)pwm);

}

/**
 * 目標角度を設定する
 * @param angle 目標角度
 */
void Tail::setCommandAngle(int angle) {
	this->commandAngle = angle;
}
