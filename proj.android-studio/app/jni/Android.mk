LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../../Classes/AppDelegate.cpp \
                   ../../../Classes/GameControllerScene.cpp \
									 ../../../Classes/Tile.cpp \
									 ../../../Classes/Level.cpp \
									 ../../../Classes/Cookie.cpp \
									 ../../../Classes/Swap.cpp \
                   ../../../Classes/GameViewScene.cpp \
									 ../../../Classes/Chain.cpp \
									 ../../../Classes/LoadingScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END

PP_STL:=c++_static
APP_CPPFLAGS += -std=c++11
NDK_TOOLCHAIN_VERSION=4.7
LOCAL_ARM_EABI=arm
LOCAL_ARM_MODE := arm
