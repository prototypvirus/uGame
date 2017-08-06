//
// Created by symbx on 05.08.17.
//

#ifndef UGAME_UTILS_H
#define UGAME_UTILS_H

#include <string>

class Utils {
public:
    static std::string getHome();
    static bool createDirectory(const std::string& dir);
    static bool isFileExists(const std::string& file);
    static void prepareDirectory(const std::string& dir);
};


#endif //UGAME_UTILS_H
