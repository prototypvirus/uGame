//
// Created by symbx on 05.08.17.
//

#ifndef UGAME_UTILS_H
#define UGAME_UTILS_H

#include <string>

namespace uGame {

    class Utils {
    public:
        static std::string getHome();

        static bool createDirectory(const std::string &dir);

        static bool isFileExists(const std::string &file);

        static void prepareDirectory(const std::string &dir);

        static std::string hashFile(const std::string file);

        static void showKeyboard(bool v);
    };
}

#endif //UGAME_UTILS_H
