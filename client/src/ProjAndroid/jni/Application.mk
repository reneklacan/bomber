APP_STL := gnustl_static
APP_CPPFLAGS := -frtti -DCOCOS2D_DEBUG=1 -std=c++11




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
