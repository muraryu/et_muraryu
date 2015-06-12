/******************************************************************************
 *  BalancingWalker.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/09
 *  前進値と旋回値をもとにバランス走行を行う
 *  シングルトン
 *  Author: muraryu
 *****************************************************************************/

#include "BalancingWalker.h"

DeclareResource(resource1);

bool BalancingWalker::insFlag = false;
BalancingWalker* BalancingWalker::instance;

/**
 * コンストラクタ
 */
BalancingWalker::BalancingWalker() {
}

/**
 * デストラクタ
 */
BalancingWalker::~BalancingWalker() {
}

BalancingWalker* BalancingWalker::getInstance() {
	if(insFlag == false){
		BalancingWalker::instance = new BalancingWalker();
		insFlag = true;
	}
	return BalancingWalker::instance;
}

/**
 * バランス走行する。
 */
void BalancingWalker::control() {
    S16 angle = mGyroSensor->getAnglerVelocity();  // ジャイロセンサ値
    S32 rightWheelEnc = mRightWheel->getCount();   // 右モータ回転角度
    S32 leftWheelEnc  = mLeftWheel->getCount();    // 左モータ回転角度

    GetResource(resource1);
    S32 forward = this->forward;
	S32 turn = this->turn;
    ReleaseResource(resource1);

    if(this->standControlMode == true) {
        mBalancer->setCommand(forward, turn);
    	mBalancer->update(angle, rightWheelEnc, leftWheelEnc, mNxt->getBattMv());

    	// 左右モータに回転を指示する
    	mLeftWheel->setPWM(mBalancer->getPwmLeft());
    	mRightWheel->setPWM(mBalancer->getPwmRight());
    }
    else {
    	mLeftWheel->setPWM(forward); // TODO しっぽで旋回
    	mRightWheel->setPWM(forward);
    }
}

/**
 * メンバの初期化＋バランス走行に必要なものをリセットする
 * @param gyroSensor ジャイロセンサ
 * @param leftWheel  左モータ
 * @param rightWheel 右モータ
 * @param nxt        NXTデバイス
 * @param balancer   バランサ
 */
void BalancingWalker::init(const ecrobot::GyroSensor* gyroSensor,
        ecrobot::Motor* leftWheel,
        ecrobot::Motor* rightWheel,
        const ecrobot::Nxt* nxt,
        Balancer* balancer) {

	// メンバ初期化
	this->mGyroSensor 	= gyroSensor;
	this->mLeftWheel 	= leftWheel;
	this->mRightWheel 	= rightWheel;
	this->mNxt 			= nxt;
	this->mBalancer 	= balancer;
	this->forward 		= 0;
	this->turn 			= 0;
	this->standControlMode = false;

	// バランス走行に必要なものをリセットする
	// ジャイロセンサオフセット初期化
    int offset = mGyroSensor->getAnglerVelocity();  // ジャイロセンサ値

    // モータエンコーダをリセットする
    mLeftWheel->reset();
    mRightWheel->reset();

    // 倒立振子制御初期化
    mBalancer->init(offset);
}

void BalancingWalker::init() {
	// ジャイロセンサオフセット初期化
    int offset = mGyroSensor->getAnglerVelocity();  // ジャイロセンサ値
    // 倒立振子制御初期化
    mBalancer->init(offset);
}

/**
 * 前進、旋回の指令値をセットする
 * @param forward 前進値
 * @param turn    旋回値
 */
void BalancingWalker::setForwardTurn(int forward, int turn) {
    GetResource(resource1);
	this->forward = forward;
	this->turn = turn;
    ReleaseResource(resource1);
}

/**
 * 総走行距離
 */
int BalancingWalker::getRunningDistance() {
	/* stub */
	return 0;
}

/**
 * 倒立制御オンオフ設定
 * @param b	オン:true, オフ:false
 */
void BalancingWalker::setStandControlMode(bool b) {
	this->standControlMode = b;
}
