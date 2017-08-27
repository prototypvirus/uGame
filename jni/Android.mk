LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := ugame

LOCAL_CFLAGS    := -std=c++11 -D_OS_ANDROID

LOCAL_C_INCLUDES := include

LOCAL_SRC_FILES := src/main.cpp src/utils/Utils.cpp src/utils/Logger.cpp src/core/Application.cpp src/core/AssetsManager.cpp src/core/PackageStream.cpp src/utils/MD5.cpp src/core/StateManager.cpp src/state/StateLoading.cpp src/state/StateMenu.cpp src/gui/Control.cpp src/gui/ControlsContainer.cpp src/gui/Window.cpp src/core/Lang.cpp src/gui/Button.cpp src/gui/UI.cpp src/gui/Label.cpp src/state/StateSignIn.cpp src/core/Config.cpp

LOCAL_SHARED_LIBRARIES := sfml-system
LOCAL_SHARED_LIBRARIES += sfml-window
LOCAL_SHARED_LIBRARIES += sfml-graphics
LOCAL_SHARED_LIBRARIES += sfml-audio
LOCAL_SHARED_LIBRARIES += sfml-network
LOCAL_WHOLE_STATIC_LIBRARIES := sfml-main
LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)

$(call import-module,sfml)

