# nxtOSEKルートディレクトリ
NXTOSEK_ROOT = ../../../../nxtOSEK

# ターゲット実行形式ファイル名
TARGET = etrobo_tr

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
	control_state/LineTraceState.cpp \
	control_state/StopState.cpp \
	control_state/TailStandUpState.cpp \
	control_state/TailWalkState.cpp \
	control_state/TailStandDownState.cpp \
	control_state/ReadyState.cpp \
	control_state/FigureFindState.cpp \
	control_state/FigureUpState.cpp \
	control_state/FigureSpinState.cpp \
	control_state/FigureDownState.cpp \
	control_state/Test1State.cpp \
	unit/BalancerCpp.cpp \
	unit/BalancingWalker.cpp \
	Main.cpp

# TOPPERS/ATK1(OSEK)設定ファイル
TOPPERS_OSEK_OIL_SOURCE = Main.oil

# 下記のマクロは変更しないでください
O_PATH ?= build

include $(NXTOSEK_ROOT)/ecrobot/ecrobot++.mak
