/******************************************************************************
 *  String.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/16
 *  Stringクラス
 *  Author: muraryu
 *****************************************************************************/

#include "Str.h"

/**
 * int型の値を文字列にして返す
 * 文字列のメモリは受け取り側で解放してください。
 */
char* Str::valueOf(int value) {

	char* str;
	int length = 1; // '\0'を除く文字数('-'含む)
	int index = 0;
	int num;
	int dev;
	bool minusFlag = false;

	// 桁数
	num = 10;
	length = 1;
	while (value / num != 0) {
		num *= 10;
		length++;
	}

	// 符号＆文字列メモリ確保
	if (value < 0) {
		length++;
		str = new char[length + 1];
		str[0] = '-';
		value*=-1;
		index++;
		minusFlag = true;
	}
	else {
		str = new char[length + 1];
	}

	dev = 1;
	while(index < length) {
		if(minusFlag == true) {
			str[length-index] = '0' + (value/dev)%10;
		}
		else {
			str[length-index-1] = '0' + (value/dev)%10;
		}
		index++;
		dev*=10;
	}

	str[length] = '\0';

	return str;

}
