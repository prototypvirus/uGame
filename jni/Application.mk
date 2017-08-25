NDK_TOOLCHAIN_VERSION := 4.9
APP_PLATFORM := android-19
# APP_STL := stlport_shared
# APP_STL := stlport_shared  --> does not seem to contain C++11 features
#APP_STL := gnustl_shared
APP_STL := c++_shared
# Enable c++11 extentions in source code
APP_CPPFLAGS += -std=c++11
APP_ABI := armeabi
APP_MODULES := sfml-activity ugame