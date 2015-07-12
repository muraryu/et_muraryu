/******************************************************************************
 *  Main.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/02/07
 *  Implementation of the Task main_task
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "Main.h"

#include "device/TouchSensor.h"
#include "app/LineMonitor.h"
#include "unit/BalancingWalker.h"
#include "util/Bluetooth.h"
#include "app/Driver.h"
#include "app/UIManager.h"
#include "app/PostureEstimation.h"

#include "control_state/CalibrationWhiteState.h"
#include "control_state/ReadyState.h"
#include "control_state/LineTraceState.h"

//#include "util/Test.h"
#include "util/Time.h"
#include "util/Str.h"

// using宣言
using ecrobot::LightSensor;
using ecrobot::GyroSensor;
using ecrobot::Motor;
using ecrobot::Nxt;
using ecrobot::TouchSensor;

// Device objects
// オブジェクトを静的に確保する
LightSensor gLightSensor(PORT_3);
GyroSensor  gGyroSensor(PORT_1);
Motor       gLeftWheel(PORT_C);
Motor       gRightWheel(PORT_B);
Motor       gTail(PORT_A);
Nxt         gNxt;
TouchSensor gTouchSensor(PORT_4);

// オブジェクトの定義
static LineMonitor			*lineMonitor;
static Balancer				*gBalancer;
static BalancingWalker		*gBalancingWalker;
static Tail					*tail;
static Driver				*driver;
static Time					*time;
static UIManager			*uiManager;
static PostureEstimation	*postureEstimation;
//static Test				*test;

extern "C" {
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

// カーネルオブジェクト宣言
DeclareCounter(SysTimerCnt);
DeclareAlarm(CyclicAlarm1); 	// 倒立制御用アラーム 4msでexpire 設定はSetRelAlarm()の引数で行う
DeclareAlarm(CyclicAlarm2); 	// bluetooth接続アラーム
DeclareAlarm(CyclicAlarm3); 	// 制御パターンアラーム
DeclareTask(InitTask);			// 最初に実行されるタスク
DeclareTask(TracerTask);		// 倒立制御用タスク 4ms周期で起動
DeclareTask(BluetoothTask);		// bluetoothタスク
DeclareTask(MainTask);			// メインタスク
DeclareResource(resource1);

/**
 * NXTシステム生成
 */
static void user_system_create() {

    // オブジェクトの作成
	lineMonitor = LineMonitor::getInstance();
	lineMonitor->init(&gLightSensor);

    gBalancer    = new Balancer();

    gBalancingWalker = BalancingWalker::getInstance();
    gBalancingWalker->init(&gGyroSensor, &gLeftWheel, &gRightWheel, &gNxt, gBalancer);

    tail = Tail::getInstance();
    tail->init(&gTail);

    driver = new Driver(new CalibrationWhiteState());
    //driver = new Driver(new ReadyState());

    time = Time::getInstance();

    uiManager = UIManager::getInstance();
    uiManager->init(&gTouchSensor);

    postureEstimation = PostureEstimation::getInstance();
    postureEstimation->init(gBalancingWalker);

    //test = new Test();
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

TASK(InitTask) {
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
 * まいまい式もついでにやる
 */
TASK(TracerTask) {

    // 4ms周期で、ライントレーサにトレース走行を依頼する
	gBalancingWalker->control();
	tail->control();

    TerminateTask();
}

/**
 * bluetoothタスク 100ms毎に起動
 */
TASK(BluetoothTask) {

	// UI監視
	uiManager->update();

    TerminateTask();
}

/**
 * メインタスク 4ms周期で起動
 * システムの各値を更新したあと、制御パターンに応じた制御を実行、制御パターン切替判断、切替を行う
 */
TASK(MainTask) {

	// 時刻を進める
	time->forward();

	// まいまい式 光センサ値更新
	lineMonitor->maimai();

	// 足角速度更新
	gBalancingWalker->updateStateVariable();

	// 姿勢状態を推定して更新
	postureEstimation->update();

	// 制御パターン実行
	driver->execute();


    TerminateTask();
}

} // end of extern "C"
