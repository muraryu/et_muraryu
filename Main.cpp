/******************************************************************************
 *  Main.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/02/07
 *  Implementation of the Task main_task
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "Main.h"

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
DeclareAlarm(CyclicAlarm);
DeclareTask(MainTask);
DeclareTask(TracerTask);

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
}

// デバイス終了用フック関数
// この関数はSTOPまたはEXITボタンが押された時に実行されます。
void ecrobot_device_terminate() {
    // センサ、モータなどの各デバイスの終了関数を
    // ここで実装することができます。
    // 周期ハンドラ停止
    CancelAlarm(CyclicAlarm);

    user_system_destroy();

    // ⇒ 光センサ赤色LEDをOFFにする
    ecrobot_set_light_sensor_inactive(NXT_PORT_S3);
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

    // 周期ハンドラ開始
    StatusType ercd = SetRelAlarm(CyclicAlarm, 1, 4);
    if (ercd != E_OK) {
        ShutdownOS(ercd);
    }

    TerminateTask();
}

TASK(TracerTask) {

	/*
	static int count;

	if(count == 100 ) {
		ecrobot_set_light_sensor_inactive(NXT_PORT_S3);
	}
	else if(count == 200) {
		ecrobot_set_light_sensor_active(NXT_PORT_S3);
		count=0;
	}
	count++;
*/

    // 4ms周期で、ライントレーサにトレース走行を依頼する
    gLineTracer->run();

    TerminateTask();
}
}
