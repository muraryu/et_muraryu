/******************************************************************************
 *  Time.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/09
 *  Definition of the Class Time
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_APP_TIME_H_
#define NXT_APP_TIME_H_

class Time {
public:
	static Time* getInstance();
	double getTime();
	void forward();

private:
	Time();
	~Time();

	static bool insFlag;	// シングルトンインスタンス生成フラグ(生成前=false, 生成後=true)
	static Time* instance;	// シングルトンインスタンス
	double time;			// インスタンス生成からの経過時間[sec]

};

#endif  // NXT_APP_TIME_H_
