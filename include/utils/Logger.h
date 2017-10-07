//
// Created by symbx on 05.08.17.
//

#ifndef UGAME_LOGGER_H
#define UGAME_LOGGER_H

#include <string>
#include <fstream>

namespace uGame {
    /**
     * Logging into console & log file (static class)
     */
    class Logger {
    public:
        /**
         * Severity (display as mark in brackets)
         */
        enum Severity {
            INFO,
            WARNING,
            ERROR,
            DEBUG
        };

        /**
         * Initialize
         * [Remove old log if exists and create new]
         * @param appDir - path to application dir
         */
        static void init(const std::string &appDir);

        /**
         * Cleanup (close and flush log)
         */
        static void clean();

        /**
         * Log message
         * @param msg - message to log
         * @param severity - severity mark
         */
        static void log(const std::string &msg, Logger::Severity severity);

        /**
         * Log message with mark [INFO]
         * @param msg - message to log
         */
        static void info(const std::string &msg);

        /**
         * Log message with mark [WARNING]
         * @param msg - message to log
         */
        static void warn(const std::string &msg);

        /**
         * Log message with mark [ERROR]
         * @param msg - message to log
         */
        static void err(const std::string &msg);

        /**
         * Log message with mark [DEBUG]
         * @param msg - message to log
         */
        static void dbg(const std::string &msg);

    protected:
        static std::ofstream *_file;

        /**
         * Write message to file
         * @param msg - message
         * @param len - length of message
         */
        static void write(const char* msg, unsigned long len);
    };

#define L_INFO Logger::info ///< Log message with mark [INFO]
#define L_WARN Logger::warn ///< Log message with mark [WARNING]
#define L_ERR Logger::err ///< Log message with mark [ERROR]
#define L_DBG Logger::dbg ///< Log message with mark [DEBUG]
}

#endif //UGAME_LOGGER_H
