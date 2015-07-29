/******************************************************************************
 *  Tail.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/09
 *  しっぽ
 *  シングルトン
 *  Author: muraryu
 *****************************************************************************/

#include "Tail.h"

#include "util/Bluetooth.h"

bool Tail::insFlag = false;
Tail* Tail::instance;

/**
 * コンストラクタ
 */
Tail::Tail()
{
	// メンバ初期化
	this->pid = new PID(2.8,0,0);
	this->commandAngle = 0;
}

/**
 * デストラクタ
 */
Tail::~Tail() {
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
 * インスタンス初期化
 */
void Tail::init(ecrobot::Motor* gTail) {

	// モーター速度と角度を0に初期化
	gTail->reset();

	// TODO 角速度計算
	this->rightAngularVelocity = 0;
	this->rightWheelEncBuf = new int[26];
	for(int i=0; i<26; i++) this->rightWheelEncBuf[i] = 0;
	this->rightWheelEncBufNext = 0;

	// メンバ初期化
	this->gTail = gTail;

}

/**
 * 目標角度に制御
 */
void Tail::control() {

	double pwm = (int)this->pid->calc(this->commandAngle, this->getAngle(), -100, 100);
	gTail->setPWM((signed char)pwm);
	//Bluetooth::sendMessage(pwm+this->gTail->getCount()*1000);
}

/**
 * 目標角度を設定する
 * @param angle 目標角度
 */
void Tail::setCommandAngle(int angle) {
	this->commandAngle = angle;
}

/**
 * しっぽ角度取得
 * @return
 */
S32 Tail::getAngle() {
	return this->gTail->getCount();
}

/**
 * 静定してからの時間(sec)を返す
 */
double Tail::saturationTime() {
	return 0; // TODO
}

/**
 * TODO
 */
double Tail::getAngularVelocity() {
	return this->rightAngularVelocity;
}

/**
 * TODO
 */
void Tail::update() {
	// 右車輪 角速度を更新（0.1sec間の角度degの差から角速度deg/secを計算）
	this->rightWheelEncBuf[this->rightWheelEncBufNext] = gTail->getCount();
	this->rightAngularVelocity = (this->rightWheelEncBuf[this->rightWheelEncBufNext] - this->rightWheelEncBuf[(this->rightWheelEncBufNext+1)%26]) * 10;
	this->rightWheelEncBufNext++;
	if(26 <= this->rightWheelEncBufNext) {
		this->rightWheelEncBufNext = 0;
	}
}
