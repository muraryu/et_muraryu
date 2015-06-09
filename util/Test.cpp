/******************************************************************************
 *  Test.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/09
 *  テスト用クラス
 *  自由にメソッド追加OK
 *  Author: muraryu
 *****************************************************************************/

#include "Test.h"

#include "util/Bluetooth.h"

extern "C"
{
#include "kernel.h"

DeclareResource(resource1);
}
/**
 * コンストラクタ
 */
Test::Test() {
	this->b1 = false;
	this->b2 = false;
}

/**
 * デストラクタ
 */
Test::~Test() {
}

/**
 * RESOURCEを使った排他制御テスト セッター
 */
void Test::exTestWrite(bool b1, bool b2) {

	GetResource(resource1);
	Bluetooth::sendMessage("write get\n");
	this->b1 = b1;
	for(int i=0; i<10000; i++);
	this->b2 = b2;
	Bluetooth::sendMessage("write release\n");
	ReleaseResource(resource1);


}

/**
 * RESOURCEを使った排他制御テスト b1 b2が違う値の時 true を返す
 */
bool Test::exTestCheck() {

	GetResource(resource1);
	if(this->b1 != this->b2) {
		ReleaseResource(resource1);
		return true;
	}
	ReleaseResource(resource1);
	return false;

}

bool Test::exTestGetB1() {
	return this->b1;
}
