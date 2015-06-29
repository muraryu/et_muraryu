/******************************************************************************
 *  PostureEstimation.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/29
 *  Definition of the Class PostureEstimation
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_APP_POSTUREESTIMATION_H_
#define NXT_APP_POSTUREESTIMATION_H_

#include "unit/BalancingWalker.h"

class PostureEstimation {
public:
	static PostureEstimation* getInstance();
	void init(BalancingWalker* balancingWalker);

	void update();			// 姿勢状態を推定して更新
	double getPosX();		// TODO Postureクラスにしてスレッドセーフにする xy同時に更新しないといけない
	double getPosY();
	double getDirection();

private:
	PostureEstimation();
	~PostureEstimation();

	static bool insFlag;						// シングルトンインスタンス生成フラグ(生成前=false, 生成後=true)
	static PostureEstimation* instance;			// シングルトンインスタンス

	BalancingWalker* balancingWalker;

	double const wheelWidth = 0.18;		// 車輪幅[m] TODO 固定パラメータをどこにするか
	double const interval = 0.004;		// 計算周期[sec] TODO 場所

	/**
	 * TODO 走行開始時の状態を原点右向きとする
	 * TODO 制御周期で更新
	 * TODO 0.1秒遅れ
	 * TODO 必ず3つ同時に更新、取得するように排他処理を行う
	 */
	double posX;		// x座標[m] TODO
	double posY;		// y座標[m] TODO
	double direction;	// 方位[deg] TODO

};

#endif  // NXT_APP_POSTUREESTIMATION_H_
