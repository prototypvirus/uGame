//
// Created by symbx on 05.08.17.
//

#include "utils/Utils.h"
#include "Constants.h"
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>

std::string& Utils::getHome() {
    std::string dir("");
#ifdef _OS_IOS

#elif _OS_ANDROID

#elif _OS_WIN32

#elif _OS_DARWIN

#elif _OS_UNIX
    struct passwd* pwd = getpwuid(getuid());
    if (pwd)
		{
			dir = pwd->pw_dir;
		}
		else
		{
			dir = getenv("HOME");
        }
    if(!dir.empty())
    {
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
