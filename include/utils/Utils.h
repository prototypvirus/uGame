//
// Created by symbx on 05.08.17.
//

#ifndef UGAME_UTILS_H
#define UGAME_UTILS_H

#include <string>

namespace uGame {

    /**
     * Additional functions exported to class
     */
    class Utils {
    public:
        /**
         * Get user home directory based on OS
         * @return
         */
        static std::string getHome();

        /**
         * Create directory with given path/name
         * @param dir - path/name of dir
         * @return success
         */
        static bool createDirectory(const std::string &dir);

        /**
         * Check file exists
         * @param file - path/name of file
         * @return exists
         */
        static bool isFileExists(const std::string &file);

        /**
         * Prepare application directory
         * @param dir - path to application dir
         */
        static void prepareDirectory(const std::string &dir);

        /**
         * Create MD5 hash of file
         * @param file - file name/path
         * @return hash
         */
        static std::string hashFile(const std::string file);

        /**
         * Show keyboard on devices with virtual keyboard
         * @param v - visible
         */
        static void showKeyboard(bool v);
    };
}

#endif //UGAME_UTILS_H
