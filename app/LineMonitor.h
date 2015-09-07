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

#include "app/Line.h"
#include "util/Time.h"

// 定義
class LineMonitor {
public:
	static LineMonitor* getInstance();
	void init(ecrobot::LightSensor* lightSensor);
    double getAdjustedBrightness();			// 現在の範囲調整済み輝度を取得 ライン種類によりフィードバック制御に差が出るのを防ぐために制御計算で用いる
    void maimai();							// 周期的に呼び出して輝度を更新する
    void calibrateWhite();					// 白のキャリブレーション
    void calibrateBlack();					// 黒のキャリブレーション
    void calibrateFigureWhite();			// フィギュアLの白のキャリブレーション
    void changeLineToNormal();				// 現在のライン種別をノーマルラインに変更
    void changeLineToGray();				// 現在のライン種別をグレーラインに変更
    void changeLineToFigure();				// 現在のライン種別をフィギュアLラインに変更
    double getBrightness();					// 現在の輝度を取得する
    bool getGrayFound();					// グレー検知フラグ 検知から1秒間だけオンになる

private:
    LineMonitor();
    virtual ~LineMonitor();

    // シングルトンパターン
	static bool insFlag;				// シングルトンインスタンス生成フラグ(生成前=false, 生成後=true)
	static LineMonitor* instance;		// シングルトンインスタンス

	// 輝度算出
    ecrobot::LightSensor* lightSensor;	// 光センサ
    double brightness;					// 光センサ値 maimai()が呼ばれるたびに更新される
    double brightnessBottom;			// 光センサ値 まいまい式用 外光のみの反射光
    short maimaiCount;					// まいまい式用カウンタ

    // ライン種別
    Line* currentLine;	// 現在のライン種別 以下の種別のうち現在走行中のインスタンスを保持する
    Line* normalLine;	// ノーマルライン
    Line* grayLine;		// グレーライン
    Line* figureLine;	// フィギュアLライン

	// グレー検知
	bool lightStable;
	int lightStableCount;
	long lightBufIndex;
	double lightBuf[16];
	bool grayFound;
	double GrayFoundTime;

    // privateメソッド
    double adjustBrightnessRange(double brightness);	// 走行中のラインのキャリブレーション上下幅で輝度を0～1の範囲に伸長して調整

};

#endif  // NXT_UNIT_LINEMONITOR_H_
