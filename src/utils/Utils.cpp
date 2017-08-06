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

std::string Utils::getHome() {
    std::string dir("");
#ifdef _OS_IOS

#elif _OS_ANDROID

#elif _OS_WIN32

#elif _OS_DARWIN

#elif _OS_UNIX
    struct passwd* pwd = getpwuid(getuid());
    if (pwd) {
        dir = pwd->pw_dir;
    } else {
        dir = getenv("HOME");
    }
    if(!dir.empty()) {
        dir.append("/");
        dir.append(GAME_DIR);
    }
#endif
    return dir;
}

bool Utils::createDirectory(const std::string &dir) {
#ifdef _OS_IOS

#elif _OS_ANDROID

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

#elif _OS_WIN32

#elif _OS_DARWIN

#elif _OS_UNIX
    return access(file.c_str(), R_OK) == 0;
#endif
    return false;
}

void Utils::prepareDirectory(const std::string &dir) {
    Utils::createDirectory(dir);
}

std::string Utils::hashFile(const std::string file) {
    std::ifstream stream(file);
    unsigned char buffer[256];
    MD5 md5;
    while(stream.read(reinterpret_cast<char *>(buffer), 256)) {
        md5.append(buffer, stream.gcount());
    }
    stream.close();
    return md5.finish();
}
