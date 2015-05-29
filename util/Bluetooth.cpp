/******************************************************************************
 *  BalancerCpp.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/02/07
 *  Implementation of the Class Balancer
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

extern "C" {
#include "ecrobot_interface.h"

}
#include "Bluetooth.h"

/**
 * コンストラクタ
 */
Bluetooth::Bluetooth() {
}

/**
 * デストラクタ
 */
Bluetooth::~Bluetooth() {
}

/**
 * バランサを初期化する
 * @param message 送信文字列 null含め最大256バイト はみ出した分は無視
 */
void Bluetooth::sendMessage(char* message) {

	U32 size;
	for(size=0; size<256; size++) {
		if(message[size] == '\0') {
			break;
		}
	}
	size++;

	ecrobot_send_bt(message, 0, size);

}

/**
 * 接続処理
 * 接続が成功してデータ送受信できる状態になると0以外を返す。
 * 戻り値が0以外になるまでこの関数を繰り返し呼び出す。
 */
int Bluetooth::connect() {

	int ret = 0;

	if(ecrobot_get_bt_status()==BT_STREAM ){
		//ecrobot_set_light_sensor_inactive(NXT_PORT_S3);
		ret = 1;
	}
	else {
		ecrobot_init_bt_slave("1234"); // ここの引数がペアリング時の値と同じ必要があるかは不明
		//ecrobot_set_light_sensor_active(NXT_PORT_S3);
		ret = 0;
	}

	return ret;
}
