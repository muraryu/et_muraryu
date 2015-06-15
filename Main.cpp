/******************************************************************************
 *  Main.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/02/07
 *  Implementation of the Task main_task
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "Main.h"

#include "util/Bluetooth.h"
#include "app/Driver.h"
#include "control_state/ReadyState.h"
#include "util/Test.h"
#include "util/Time.h"

// using宣言
using ecrobot::LightSensor;
using ecrobot::GyroSensor;
using ecrobot::Motor;
using ecrobot::Nxt;

// Device objects
// オブジェクトを静的に確保する
LightSensor gLightSensor(PORT_3);
GyroSensor  gGyroSensor(PORT_1);
Motor       gLeftWheel(PORT_C);
Motor       gRightWheel(PORT_B);
Motor       gTail(PORT_A);
Nxt         gNxt;
bool Bluetooth::readyFlag;

// オブジェクトの定義
static Balancer			*gBalancer;
static BalancingWalker	*gBalancingWalker;
static Tail				*tail;
static Driver			*driver;
static Time				*time;
static Test				*test;

extern "C" {
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "balancer_param.c"

// カーネルオブジェクト宣言
DeclareCounter(SysTimerCnt);
DeclareAlarm(CyclicAlarm1); 	// 倒立制御用アラーム 4msでexpire 設定はSetRelAlarm()の引数で行う
DeclareAlarm(CyclicAlarm2); 	// bluetooth接続アラーム
DeclareAlarm(CyclicAlarm3); 	// 制御パターンアラーム
DeclareTask(MainTask);			// 最初に実行されるタスク
DeclareTask(TracerTask);		// 倒立制御用タスク 4ms周期で起動
DeclareTask(BluetoothTask);		// bluetoothタスク
DeclareTask(ControlPattern);	// 制御パターンタスク
DeclareResource(resource1);

/**
 * NXTシステム生成
 */
static void user_system_create() {

    // オブジェクトの作成
    gBalancer    = new Balancer();

    gBalancingWalker = BalancingWalker::getInstance();
    gBalancingWalker->init(&gGyroSensor, &gLeftWheel, &gRightWheel, &gNxt, gBalancer);

    tail = Tail::getInstance();
    tail->init(&gTail);

    driver = new Driver(new ReadyState());

    time = Time::getInstance();

    test = new Test();

    Bluetooth::readyFlag = false;
}

/**
 * NXTシステム破棄
 */
static void user_system_destroy() {
    delete gBalancingWalker;
    delete gBalancer;
}

// デバイス初期化用フック関数
// この関数はnxtOSEK起動時に実行されます。
void ecrobot_device_initialize() {
    // センサ、モータなどの各デバイスの初期化関数を
    // ここで実装することができます

    // ⇒ 光センサ赤色LEDをONにする
    ecrobot_set_light_sensor_active(NXT_PORT_S3);

}

// デバイス終了用フック関数
// この関数はSTOPまたはEXITボタンが押された時に実行されます。
void ecrobot_device_terminate() {
    // センサ、モータなどの各デバイスの終了関数を
    // ここで実装することができます。
    // 周期ハンドラ停止
    CancelAlarm(CyclicAlarm1);
    CancelAlarm(CyclicAlarm2);
    CancelAlarm(CyclicAlarm3);

    user_system_destroy();

    // ⇒ 光センサ赤色LEDをOFFにする
    ecrobot_set_light_sensor_inactive(NXT_PORT_S3);

	// ⇒Bluetooth通信終了処理を行う
	ecrobot_term_bt_connection();

}

// 1msec周期割り込み(ISRカテゴリ2)から起動されるユーザー用フック関数
void user_1ms_isr_type2(void) {
    StatusType ercd = SignalCounter(SysTimerCnt);
    if (ercd != E_OK) {
        ShutdownOS(ercd);
    }
}

TASK(MainTask) {
    user_system_create();

    StatusType ercd;
    // 周期ハンドラ開始

    // 倒立制御タスク開始
    ercd = SetRelAlarm(CyclicAlarm1, 1, 4);
    if (ercd != E_OK) {
        ShutdownOS(ercd);
    }

    // Bluetoothタスク開始
    ercd = SetRelAlarm(CyclicAlarm2, 1, 100);
    if (ercd != E_OK) {
        ShutdownOS(ercd);
    }

    // 制御パターンタスク開始
    ercd = SetRelAlarm(CyclicAlarm3, 1, 4);
    if (ercd != E_OK) {
        ShutdownOS(ercd);
    }

    TerminateTask();
}

/**
 * 倒立制御用タスク 4ms周期で起動
 * 時間管理もついでにやる
 */
TASK(TracerTask) {

    // 4ms周期で、ライントレーサにトレース走行を依頼する
	gBalancingWalker->control();
	tail->control();

	// 時刻を進める
	time->forward();

    TerminateTask();
}

/**
 * bluetoothタスク 100ms毎に起動
 */
TASK(BluetoothTask) {

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
			} else if(buf[0] == '1') {
				Bluetooth::readyFlag = true;
			}

		}
	}

    TerminateTask();
}

/**
 * 制御パターンタスク 4ms周期で起動
 * 制御パターンに応じた制御を実行、制御パターン切替判断、切替を行う
 */
TASK(ControlPattern) {

    driver->execute();

    TerminateTask();
}

} // end of extern "C"
