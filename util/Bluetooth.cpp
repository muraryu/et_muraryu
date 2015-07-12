/******************************************************************************
 *  Bluetooth.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/23
 *  Bluetooth関連の処理
 *  Author: muraryu
 *****************************************************************************/

extern "C" {
#include "ecrobot_interface.h"
}
#include "Bluetooth.h"
#include "util/Str.h"

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
 * Null文字までの文字列を送信する
 * 処理速度向上のため、文字数が分かっている場合は、
 * sendMessage(char* message, int length)を使用してください。
 * @param message 送信文字列 null含め最大256バイト はみ出した分は無視
 */
void Bluetooth::sendMessage(char* message) {

	U32 size;
	for(size=0; size<256; size++) {
		if(message[size] == '\0') {
			size++;
			break;
		}
	}

	ecrobot_send_bt(message, 0, size);

}

/**
 * サイズを指定して文字列を送信する
 * 大量に送信する際に推奨
 * @param message 	送信文字列 null含め最大256バイト サイズ以降は無視
 * @param size		nullを含めたサイズ
 */
void Bluetooth::sendMessage(char* message, int size) {

	ecrobot_send_bt(message, 0, size);

}

/**
 * int型の数値を送信する
 */
void Bluetooth::sendMessage(int value) {
	char* str = Str::valueOf(value);
	Bluetooth::sendMessage(str);
	delete[] str;
}

/**
 * サイズを指定して文字列を受信する
 * @param message	受信バッファ
 * @param len		受信バッファサイズ
 */
int Bluetooth::receiveMessage(char* message, int len) {

	int size = ecrobot_read_bt(message, 0, len);

	message[size] = '\0';

	return size;

}

/**
 * 接続処理
 * 接続が成功してデータ送受信できる状態になると0以外を返す。
 * 戻り値が0以外になるまでこの関数を繰り返し呼び出す。
 */
bool Bluetooth::connect() {

	bool ret = false;

	if(ecrobot_get_bt_status()==BT_STREAM ){
		//ecrobot_set_light_sensor_inactive(NXT_PORT_S3);
		//ecrobot_set_bt_device_name("ET247");
		sendMessage("\nbluetooth connected\n>");
		ret = true;
	}
	else {
		ecrobot_init_bt_slave("1234"); // ここの引数がペアリング時の値と同じ必要があるかは不明
		//ecrobot_set_light_sensor_active(NXT_PORT_S3);
		ret = false;
	}

	return ret;
}

/**
 * ecrobot_bt_data_logger
 * これを使うときは他のデータを送らないようにしないとcsvがバグる
 * このクラスのecrobot_send_bt()使ってるところをコメントアウトする等すればＯＫ
 */
void Bluetooth::dataLogger(signed char data1, signed char data2) {
	ecrobot_bt_data_logger(data1, data2);
}
