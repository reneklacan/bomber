LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := hellocpp_shared

LOCAL_MODULE_FILENAME := libhellocpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
        ../../Classes/AppDelegate.cpp \
        ../../Classes/GameplayScene.cpp \
        ../../Classes/GameOverScene.cpp \
        ../../Classes/Input/Joystick.cpp \
        ../../Classes/Input/Keyboard.cpp \
        ../../Classes/Input/ControlLayer.cpp \
        ../../Classes/Gameplay/LevelLayer.cpp \
        ../../Classes/Gameplay/Map/Map.cpp \
        ../../Classes/Gameplay/Map/Bomb.cpp \
        ../../Classes/Gameplay/Map/Explosion.cpp \
        ../../Classes/Gameplay/Sprites/GameSprite.cpp \
        ../../Classes/Gameplay/Sprites/Human.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static

#APP_ABI := armeabi armeabi-v7a

DIRECTIVES := ANDROID

# Target Android.mk
APP_PLATFORM := android-9
#
# ## Compiles in debug/release mode
APP_OPTIM := release
#
# ## Defines ARMv7 ABI only (will drop ARMv6 CPUs). You can define several ABIs, and let device choose best one.
APP_ABI := armeabi-v7a
#
# ## Override flags for debug !
# APP_CFLAGS := -O0 -g -ggdb
#
# ## Override flags for speed !
APP_CFLAGS := -Os -ffast-math -funroll-loops -fomit-frame-pointer -fno-strict-aliasing
APP_CPPFLAGS += -frtti
#
# # Use STL ?
APP_STL := gnustl_static
#
# In order to switch between ARM/THUMB edit your Android.mk with this directive :
#
# # Compile to ARM/THUMB for speed
LOCAL_ARM_MODE	:= arm

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)

