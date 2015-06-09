/******************************************************************************
 *  Tail.cpp (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/09
 *  しっぽ
 *  Author: muraryu
 *****************************************************************************/

#include "Tail.h"

static Tail* instance = Tail::getInstance();

/**
 * コンストラクタ
 */
Tail::Tail() {
}

/**
 * インスタンス取得
 */
Tail* Tail::getInstance() {

	return instance;
}
