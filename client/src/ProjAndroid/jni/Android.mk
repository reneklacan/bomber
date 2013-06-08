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
        ../../Classes/Gameplay/Map/Map.cpp \
        ../../Classes/Gameplay/Map/Bomb.cpp \
        ../../Classes/Gameplay/Map/Explosion.cpp \
        ../../Classes/Gameplay/Sprites/GameSprite.cpp \
        ../../Classes/Gameplay/Sprites/Human.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static

APP_ABI := armeabi armeabi-v7a

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)

