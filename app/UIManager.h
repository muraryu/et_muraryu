/******************************************************************************
 *  UIManager.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/29
 *  Definition of the Class UIManager
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_APP_UIMANAGER_H_
#define NXT_APP_UIMANAGER_H_

#include "device/TouchSensor.h"
#include "util/Time.h"

class UIManager {
public:
	static UIManager* getInstance();
	void init(ecrobot::TouchSensor* touchSensor);

	void update();						// ユーザからの情報を監視して更新
	bool isButtonPressed();				// タッチボタンが押されたかを取得
	void resetButtonPressed();					// タッチボタンの情報をリセット
	bool isReadyToStart();				// 走行開始合図を取得
	void resetReadyToStart();				// 走行開始合図をリセット

private:
	UIManager();
	~UIManager();

	static bool insFlag;				// シングルトンインスタンス生成フラグ(生成前=false, 生成後=true)
	static UIManager* instance;			// シングルトンインスタンス

	Time* time;							// 時間インスタンス
	ecrobot::TouchSensor* touchSensor;	// タッチセンサインスタンス

	bool isButtonPressedFlag;			// タッチボタンが押されたフラグ
	double buttonPressedStartTime;		// タッチボタンが押された時刻
	bool isReadyToStartFlag;			// 走行開始合図のフラグ


};

#endif  // NXT_APP_UIMANAGER_H_
