/******************************************************************************
 *  LineMonitor.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/02/07
 *  Definition of the Class LineMonitor
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef NXT_UNIT_LINEMONITOR_H_
#define NXT_UNIT_LINEMONITOR_H_

#include "LightSensor.h"

// 定義
class LineMonitor {
public:
	static LineMonitor* getInstance();
	void init(ecrobot::LightSensor* lightSensor);
    double getBrightness();
    void maimai();							// 周期的に呼び出して輝度を更新する
    void calibrateWhite();					// 白のキャリブレーションと白黒の境界値更新
    void calibrateBlack();					// 黒のキャリブレーションと白黒の境界値更新
    void calibrateFigureWhite();			// フィギュアLの白のキャリブレーションと白黒の境界値更新
    double getBorderBrightness();			// 白黒の境界地を取得する
    double getBorderFigureBrightness();		// フィギュアLの白黒の境界地を取得する
    void setBorderBrightness(double val); //臨時

private:
    LineMonitor();
    virtual ~LineMonitor();

	static bool insFlag;				// シングルトンインスタンス生成フラグ(生成前=false, 生成後=true)
	static LineMonitor* instance;		// シングルトンインスタンス

    ecrobot::LightSensor* lightSensor;	// 光センサ
    double brightness;					// 光センサ値 maimai()が呼ばれるたびに更新される
    double brightnessBottom;			// 光センサ値 まいまい式用 外光のみの反射光
    short maimaiCount;					// まいまい式用カウンタ
    double whiteBrightness;				// 白のキャリブレーション値
    double blackBrightness;				// 黒のキャリブレーション値
    double whiteFigureBrightness;		// フィギュアLの白のキャリブレーション値
    double borderBrightness;			// 白黒の境界値（トレース時の目標値）
    double borderFigureBrightness;		// フィギュアLの白黒の境界値（トレース時の目標値）
};

#endif  // NXT_UNIT_LINEMONITOR_H_
