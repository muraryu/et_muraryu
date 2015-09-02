# nxtOSEKルートディレクトリ
NXTOSEK_ROOT = ../../../../nxtOSEK

# ターゲット実行形式ファイル名
TARGET = et2015

# インクルードパス
USER_INC_PATH = \
	$(NXTOSEK_ROOT)/ecrobot/nxtway_gs_balancer \
	app \
	unit

# ライブラリ
USER_LIB = nxtway_gs_balancer

# Cソースファイル
TARGET_SOURCES = balancer_param.c

# CPPソースファイル
TARGET_CPP_SOURCES = \
	util/Bluetooth.cpp \
	util/PID.cpp \
	util/Test.cpp \
	util/Time.cpp \
	util/Str.cpp \
	app/Driver.cpp \
	app/Tail.cpp \
	app/LineMonitor.cpp \
	app/UIManager.cpp \
	app/PostureEstimation.cpp \
	app/Line.cpp \
	control_state/CalibrationWhiteState.cpp \
	control_state/CalibrationBlackState.cpp \
	control_state/CalibrationFigureWhiteState.cpp \
	control_state/LineTraceState.cpp \
	control_state/StopState.cpp \
	control_state/LookupFindState.cpp \
	control_state/LookupSitDownState.cpp \
	control_state/LookupPassState.cpp \
	control_state/LookupStandUpState.cpp \
	control_state/GarageLApproachState.cpp \
	control_state/ReadyState.cpp \
	control_state/StartState.cpp \
	control_state/FigureFindState.cpp \
	control_state/FigureSitDownState.cpp \
	control_state/FigureBackState.cpp \
	control_state/FigureUpState.cpp \
	control_state/FigureTailUpState.cpp \
	control_state/FigureStopState.cpp \
	control_state/FigureSpinState.cpp \
	control_state/FigureStandUpState.cpp \
	control_state/FigureLineTraceState.cpp \
	control_state/GarageRApproachState.cpp \
	control_state/GarageStopState.cpp \
	control_state/Test1State.cpp \
	device/TouchSensor.cpp \
	device/SonarSensor.cpp \
	unit/BalancerCpp.cpp \
	unit/BalancingWalker.cpp \
	Main.cpp

# TOPPERS/ATK1(OSEK)設定ファイル
TOPPERS_OSEK_OIL_SOURCE = Main.oil

# 下記のマクロは変更しないでください
O_PATH ?= build

include $(NXTOSEK_ROOT)/ecrobot/ecrobot++.mak
