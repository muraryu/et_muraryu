/******************************************************************************
 *  Main.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/02/07
 *  Implementation of the Task main_task
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "Main.h"
#include "util/Bluetooth.h"

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
Nxt         gNxt;

// オブジェクトの定義
static LineMonitor     *gLineMonitor;
static Balancer        *gBalancer;
static BalancingWalker *gBalancingWalker;
static LineTracer      *gLineTracer;

extern "C" {
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

// カーネルオブジェクト宣言
DeclareCounter(SysTimerCnt);
DeclareAlarm(CyclicAlarm1); // 倒立制御用アラーム 4msでexpire 設定はSetRelAlarm()の引数で行う
DeclareAlarm(CyclicAlarm2); // bluetooth接続アラーム
DeclareTask(MainTask);		// 最初に実行されるタスク
DeclareTask(TracerTask);	// 倒立制御用タスク 4ms周期で起動
DeclareTask(BluetoothTask);	// bluetooth接続タスク

/**
 * NXTシステム生成
 */
static void user_system_create() {
    // オブジェクトの作成
    gLineMonitor = new LineMonitor(gLightSensor);
    gBalancer    = new Balancer();
    gBalancingWalker = new BalancingWalker(gGyroSensor,
                                           gLeftWheel,
                                           gRightWheel,
                                           gNxt,
                                           gBalancer);
    gLineTracer = new LineTracer(gLineMonitor, gBalancingWalker);
}

/**
 * NXTシステム破棄
 */
static void user_system_destroy() {
    delete gLineTracer;
    delete gBalancingWalker;
    delete gBalancer;
    delete gLineMonitor;
}

// デバイス初期化用フック関数
// この関数はnxtOSEK起動時に実行されます。
void ecrobot_device_initialize() {
    // センサ、モータなどの各デバイスの初期化関数を
    // ここで実装することができます

    // ⇒ 光センサ赤色LEDをONにする
    ecrobot_set_light_sensor_active(NXT_PORT_S3);

    /*
	// ⇒Bluetooth通信開始処理を行う
	// デバイス名を設定します// デバイス名は重複しないようにET + チームIDとします
	if(ecrobot_get_bt_status()==BT_NO_INIT){
		ecrobot_set_bt_device_name("ET38");
	}
	// bluetooth通信のスレーブデバイスとして初期化します
	// 引数はパスキーです
	ecrobot_init_bt_slave("1234");
*/
}

// デバイス終了用フック関数
// この関数はSTOPまたはEXITボタンが押された時に実行されます。
void ecrobot_device_terminate() {
    // センサ、モータなどの各デバイスの終了関数を
    // ここで実装することができます。
    // 周期ハンドラ停止
    CancelAlarm(CyclicAlarm1);

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

    // Bluetooth接続タスク開始
    ercd = SetRelAlarm(CyclicAlarm2, 1, 100);
    if (ercd != E_OK) {
        ShutdownOS(ercd);
    }

    TerminateTask();
}

/**
 * 倒立制御用タスク 4ms周期で起動
 */
TASK(TracerTask) {

	Bluetooth::sendMessage("111111\n");

    // 4ms周期で、ライントレーサにトレース走行を依頼する
    //gLineTracer->run();

    TerminateTask();
}

/**
 * bluetooth接続タスク 100ms毎に起動
 */
TASK(BluetoothTask) {

	Bluetooth::connect();
	Bluetooth::sendMessage("22222\n");

    // 4ms周期で、ライントレーサにトレース走行を依頼する
    //gLineTracer->run();
    TerminateTask();
}

} // end of extern "C"
