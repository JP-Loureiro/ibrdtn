LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := android-glue
LOCAL_SRC_FILES = \
	JNIHelp.cpp \
	Helper.cpp \
	JNI_OnLoad.cpp \
	NativeDaemonWrapper.cpp \
	SWIGWrapper.cpp

LOCAL_C_INCLUDES :=\
	$(LOCAL_PATH) \
	$(LOCAL_PATH)/../dtnd/src

LOCAL_SHARED_LIBRARIES :=\
	ibrcommon \
	ibrdtn \
	dtnd

LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
