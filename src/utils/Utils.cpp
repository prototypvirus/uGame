//
// Created by symbx on 05.08.17.
//

#include "utils/Utils.h"
#include "Constants.h"
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <fstream>
#include <utils/MD5.h>
#ifdef _OS_ANDROID
#include <jni.h>
#include <android/native_activity.h>
#include <SFML/System/NativeActivity.hpp>
#include "utils/Logger.h"
#endif

namespace uGame {

    std::string Utils::getHome() {
        std::string dir("");
#ifdef _OS_IOS

#elif _OS_ANDROID
        ANativeActivity *activity = sf::getNativeActivity();
        JNIEnv* env = activity->env;
        activity->vm->AttachCurrentThread(&env, NULL);
        jclass cls_Env = env->FindClass("android/app/NativeActivity");
        jmethodID mid = env->GetMethodID(cls_Env, "getExternalFilesDir", "(Ljava/lang/String;)Ljava/io/File;");
        jobject obj_File = env->CallObjectMethod(activity->clazz, mid, NULL);
        jclass cls_File = env->FindClass("java/io/File");
        jmethodID mid_getPath = env->GetMethodID(cls_File, "getPath", "()Ljava/lang/String;");
        jstring obj_Path = (jstring) env->CallObjectMethod(obj_File, mid_getPath);
        const char *cstr = env->GetStringUTFChars(obj_Path, NULL);
        dir = std::string(cstr);
        env->ReleaseStringUTFChars(obj_Path, cstr);
        return dir;
#elif _OS_WIN32

#elif _OS_DARWIN

#elif _OS_UNIX
        struct passwd *pwd = getpwuid(getuid());
        if (pwd) {
            dir = pwd->pw_dir;
        } else {
            dir = getenv("HOME");
        }
        if (!dir.empty()) {
            dir.append("/");
            dir.append(GAME_DIR);
        }
#endif
        return dir;
    }

    bool Utils::createDirectory(const std::string &dir) {
#ifdef _OS_IOS

#elif _OS_ANDROID
        return mkdir(dir.c_str(), 0755) != 0;
#elif _OS_WIN32

#elif _OS_DARWIN

#elif _OS_UNIX
        return mkdir(dir.c_str(), 0755) != 0;
#endif
        return true;
    }

    bool Utils::isFileExists(const std::string &file) {
#ifdef _OS_IOS

#elif _OS_ANDROID
        int acs = access(file.c_str(), R_OK);
        return acs == 0;
#elif _OS_WIN32

#elif _OS_DARWIN

#elif _OS_UNIX
        int acs = access(file.c_str(), R_OK);
        return acs == 0;
#else
        return false;
#endif
    }

    void Utils::prepareDirectory(const std::string &dir) {
        Utils::createDirectory(dir);
    }

    std::string Utils::hashFile(const std::string file) {
        std::ifstream stream(file, std::ifstream::binary);
        unsigned char buffer[1024];
        MD5 md5;
        while (stream.read(reinterpret_cast<char *>(buffer), 1024)) {
            md5.update(buffer, stream.gcount());
        }
        int last = stream.gcount();
        if (last > 0) {
            md5.update(buffer, last);
        }
        stream.close();
        md5.finalize();
        return md5.hexdigest();
    }
}