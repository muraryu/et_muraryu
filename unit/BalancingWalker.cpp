/******************************************************************************
 *  BalancingWalker.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/09
 *  前進値と旋回値をもとにバランス走行を行う
 *  シングルトン
 *  Author: muraryu
 *****************************************************************************/

#include "BalancingWalker.h"
#include "util/Bluetooth.h"
#include "util/Str.h"

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
    S32 rightWheelEnc = mRightWheel->getCount();// - this->rightWheelEncOffset;   // 右モータ回転角度
    S32 leftWheelEnc  = mLeftWheel->getCount();// - this->rightWheelEncOffset;    // 左モータ回転角度

    // 前進値と旋回値を取得
    GetResource(resource1);
    S32 forward = this->forward;
	S32 turn = this->turn;
    ReleaseResource(resource1);

    // 倒立制御オンの場合はバランサーによりPWMを設定
    if(this->standControlMode == true) {
        mBalancer->setCommand(forward, turn);
    	mBalancer->update(angle, rightWheelEnc, leftWheelEnc, mNxt->getBattMv());

    	//Bluetooth::sendMessage(mBalancer->getPwmLeft()*1000+mBalancer->getPwmRight());

    	// 左右モータに回転を指示する
    	mLeftWheel->setPWM(mBalancer->getPwmLeft());
    	mRightWheel->setPWM(mBalancer->getPwmRight());
    }
    else {
    	mLeftWheel->setPWM((S8)(forward + turn*1.0)); // TODO しっぽで走行するときの旋回と前進のPWM計算
    	mRightWheel->setPWM((S8)(forward - turn*1.0));//      現状適当 前進量と進行方向速度、旋回量と旋回角速度が比例するようにする
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
	this->mGyroSensor 		= gyroSensor;
	this->mLeftWheel 		= leftWheel;
	this->mRightWheel 		= rightWheel;
	this->mNxt 				= nxt;
	this->mBalancer 		= balancer;
	this->forward 			= 0;
	this->turn 				= 0;
	this->garageDistance	= 0;

	this->standControlMode = false;

	this->rightWheelEncOffset = 0;
	this->leftWheelEncOffset = 0;

	this->rightAngularVelocity = 0;
	this->rightWheelEncBuf = new int[26];
	for(int i=0; i<26; i++) this->rightWheelEncBuf[i] = 0;
	this->rightWheelEncBufNext = 0;

	this->leftAngularVelocity = 0;
	this->leftWheelEncBuf = new int[26];
	for(int i=0; i<26; i++) this->leftWheelEncBuf[i] = 0;
	this->leftWheelEncBufNext = 0;

	// バランス走行に必要なものをリセットする
	// ジャイロセンサオフセット初期化
    this->offset = mGyroSensor->getAnglerVelocity();  // ジャイロセンサ値

    // モータエンコーダをリセットする
    mLeftWheel->reset();
    mRightWheel->reset();

    // 倒立振子制御初期化
    mBalancer->init(this->offset);

    // 再初期化時
    this->offsetRightEncBeforeInit = 0;
}

void BalancingWalker::init() {
	// ジャイロセンサオフセット初期化
    //int offset = mGyroSensor->getAnglerVelocity();  // ジャイロセンサ値

    // ガレージ距離調整
    this->offsetRightEncBeforeInit += this->getRightEnc();

	// モータエンコーダをリセットする
    mLeftWheel->reset();
    mRightWheel->reset();

    // 倒立振子制御初期化
    mBalancer->init(this->offset);

}

/**
 * 前進、旋回の指令値をセットする
 * 同時に、ライントレースモードを解除する
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
 * 倒立制御オンオフ設定
 * @param b	オン:true, オフ:false
 */
void BalancingWalker::setStandControlMode(bool b) {

	// モードが変化するときのみ処理
	if(this->standControlMode == true && b == false) {
		this->rightWheelEnc = mRightWheel->getCount();
		this->leftWheelEnc = mLeftWheel->getCount();
	}
	else if(this->standControlMode == false && b == true) {
		this->rightWheelEncOffset = mRightWheel->getCount() - this->rightWheelEnc;
		this->leftWheelEncOffset = mLeftWheel->getCount() - this->leftWheelEnc;
		this->init();
	}

	this->standControlMode = b;
}

/**
 * 倒立制御オンオフ取得
 */
bool BalancingWalker::getStandControlMode() {
	return this->standControlMode;
}

/**
 * 右モーター角度を返す
 * @return モーター角度deg
 */
int BalancingWalker::getRightEnc() {
	return mRightWheel->getCount();
}

/**
 * 左モーター角度を返す
 * @return モーター角度deg
 */
int BalancingWalker::getLeftEnc() {
	return mLeftWheel->getCount();
}

/**
 * 右モーター角速度を取得する
 * @return モーター角速度deg/sec
 */
int BalancingWalker::getRightAngularVelocity() {
	return this->rightAngularVelocity;
}

/**
 * 左モーター角速度を取得する
 * @return モーター角速度deg/sec
 */
int BalancingWalker::getLeftAngularVelocity() {
	return this->leftAngularVelocity;
}

/**
 * 状態量を再計算
 * 車輪角速度
 * TODO モータークラスに持たせるそのうち
 */
void BalancingWalker::updateStateVariable() {

	// 右車輪 角速度を更新（0.1sec間の角度degの差から角速度deg/secを計算）
	this->rightWheelEncBuf[this->rightWheelEncBufNext] = mRightWheel->getCount();
	this->rightAngularVelocity = (this->rightWheelEncBuf[this->rightWheelEncBufNext] - this->rightWheelEncBuf[(this->rightWheelEncBufNext+1)%26]) * 10;
	this->rightWheelEncBufNext++;
	if(26 <= this->rightWheelEncBufNext) {
		this->rightWheelEncBufNext = 0;
	}

	// 左車輪 角速度を更新（0.1sec間の角度degの差から角速度deg/secを計算）
	this->leftWheelEncBuf[this->leftWheelEncBufNext] = mLeftWheel->getCount();
	this->leftAngularVelocity = (this->leftWheelEncBuf[this->leftWheelEncBufNext] - this->leftWheelEncBuf[(this->leftWheelEncBufNext+1)%26]) * 10;
	this->leftWheelEncBufNext++;
	if(26 <= this->leftWheelEncBufNext) {
		this->leftWheelEncBufNext = 0;
	}

}

/**
 * ガレージまでの車輪角度[deg]をセットする
 */
void BalancingWalker::notifyGarageDistance(int distance) {
	this->garageDistance = this->getRightEnc() + this->offsetRightEncBeforeInit + distance;
}

/**
 * ガレージまでの車輪角度[deg]を取得する
 */
int BalancingWalker::calcGarageDistance() {
	return this->garageDistance - this->getRightEnc() - this->offsetRightEncBeforeInit;
}
