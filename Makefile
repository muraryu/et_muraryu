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
	app/LineTracer.cpp \
	unit/BalancerCpp.cpp \
	unit/BalancingWalker.cpp \
	unit/LineMonitor.cpp \
	Main.cpp

# TOPPERS/ATK1(OSEK)設定ファイル
TOPPERS_OSEK_OIL_SOURCE = Main.oil

# 下記のマクロは変更しないでください
O_PATH ?= build

include $(NXTOSEK_ROOT)/ecrobot/ecrobot++.mak
