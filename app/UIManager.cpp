/******************************************************************************
 *  UIManager.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/29
 *  UI管理
 *  シングルトン
 *  Author: muraryu
 *****************************************************************************/

#include "UIManager.h"

#include "util/Bluetooth.h"
#include "balancer_param.c"

bool UIManager::insFlag = false;
UIManager* UIManager::instance;

/**
 * コンストラクタ
 */
UIManager::UIManager()
{
	// メンバ初期化
	this->time = Time::getInstance();
	this->isButtonPressedFlag = false;
	this->isReadyToStartFlag = false;
	this->buttonPressedStartTime = this->time->getTime();
}

/**
 * デストラクタ
 */
UIManager::~UIManager() {
}

/**
 * インスタンス取得
 */
UIManager* UIManager::getInstance() {
	if(insFlag == false){
		UIManager::instance = new UIManager();
		insFlag = true;
	}
	return UIManager::instance;
}

/**
 * インスタンス初期化
 */
void UIManager::init(ecrobot::TouchSensor* touchSensor) {

	// メンバ初期化
	this->touchSensor = touchSensor;

}

/**
 * ユーザからの情報を監視して更新
 */
void UIManager::update() {

	// タッチボタンが押されたか チャタリング防止して判断
	if(this->touchSensor->isPressed() == true) {
		// 規定時間以上ボタンが押された
		if(0.5 < this->time->getTime() - this->buttonPressedStartTime) {
			this->isButtonPressedFlag = true;
		}
	}
	else {
		this->buttonPressedStartTime = this->time->getTime();
	}

	// 走行開始合図があったか TODO 接続処理をどうするか
	static char buf[128];
	static bool cflag = false;

	buf[0] = '\0';

	if(cflag == false) {
		cflag = Bluetooth::connect();
	}
	else {
		if(Bluetooth::receiveMessage(buf, 128) != 0) {
			buf[1] = '\n';
			buf[2] = buf[0];
			buf[3] = '\n';
			buf[4] = '>';
			buf[5] = '\0';

			Bluetooth::sendMessage(buf);

			if(buf[0] == 'q') {
				K_F[0] += 0.1F;
			} else if(buf[0] == 'a') {
				K_F[0] -= 0.1F;
			} else if(buf[0] == 'w') {
				K_F[1] += 0.1F;
			} else if(buf[0] == 's') {
				K_F[1] -= 0.1F;
			} else if(buf[0] == 'e') {
				K_F[2] += 0.1F;
			} else if(buf[0] == 'd') {
				K_F[2] -= 0.1F;
			} else if(buf[0] == 'r') {
				K_F[3] += 0.1F;
			} else if(buf[0] == 'f') {
				K_F[3] -= 0.1F;
			} else if(buf[0] == 't') {
				K_THETADOT += 0.1F;
			} else if(buf[0] == 'g') {
				K_THETADOT -= 0.1F;
			} else if(buf[0] == '1') {
				this->isReadyToStartFlag = true;
			} else if(buf[0] == 'j') {
				mura_p -= 10;
			} else if(buf[0] == 'u') {
				mura_p += 10;
			} else if(buf[0] == 'k') {
				mura_d -= 50;
			} else if(buf[0] == 'i') {
				mura_d += 50;
			}

		}
	}
}

/**
 * タッチボタンが押されたかを取得
 */
bool UIManager::isButtonPressed() {
	return this->isButtonPressedFlag;
}

/**
 * タッチボタンの情報をリセット
 */
void UIManager::resetButtonPressed() {
	this->isButtonPressedFlag = false;
	this->buttonPressedStartTime = this->time->getTime();
}

/**
 * 走行開始合図を取得
 */
bool UIManager::isReadyToStart() {
	return this->isReadyToStartFlag;
}

/**
 * 走行開始合図をリセット
 */
void UIManager::resetReadyToStart() {
	this->isReadyToStartFlag = false;
}
