//
// Created by symbx on 05.08.17.
//

#include <iostream>
#include "utils/Logger.h"
#ifdef _OS_ANDROID
#include <android/log.h>
#endif

namespace uGame {

    std::ofstream *Logger::_file;

    void Logger::init(const std::string &appDir) {
        std::string app(appDir);
        app.append("/latest.log");
        remove(app.c_str());
        Logger::_file = new std::ofstream(app);
    }

    void Logger::clean() {
        Logger::_file->close();
        delete Logger::_file;
    }

    void Logger::log(const std::string &msg, Logger::Severity severity) {
#ifdef _OS_ANDROID
        switch (severity) {
            case INFO:
                __android_log_print(ANDROID_LOG_VERBOSE, GAME_NAME, "[INFO] %s", msg.c_str());
                Logger::_file->write("[INFO] ", 7);
                break;
            case WARNING:
                __android_log_print(ANDROID_LOG_VERBOSE, GAME_NAME, "[WARNING] %s", msg.c_str());
                Logger::_file->write("[WARNING] ", 10);
                break;
            case ERROR:
                __android_log_print(ANDROID_LOG_VERBOSE, GAME_NAME, "[ERROR] %s", msg.c_str());
                Logger::_file->write("[ERROR] ", 8);
                break;
            case DEBUG:
                __android_log_print(ANDROID_LOG_VERBOSE, GAME_NAME, "[DEBUG] %s", msg.c_str());
                Logger::_file->write("[DEBUG] ", 8);
                break;
        }
#else
        switch (severity) {
            case INFO:
                Logger::_file->write("[INFO] ", 7);
                std::cout << "[INFO] ";
                break;
            case WARNING:
                Logger::_file->write("[WARNING] ", 10);
                std::cout << "[WARNING] ";
                break;
            case ERROR:
                Logger::_file->write("[ERROR] ", 8);
                std::cout << "[ERROR] ";
                break;
            case DEBUG:
                Logger::_file->write("[DEBUG] ", 8);
                std::cout << "[DEBUG] ";
                break;
        }
        Logger::_file->write(msg.c_str(), msg.length());
        Logger::_file->write("\r\n", 2);
        std::cout << msg << std::endl;
#endif
    }

    void Logger::info(const std::string &msg) {
        Logger::log(msg, INFO);
    }

    void Logger::warn(const std::string &msg) {
        Logger::log(msg, WARNING);
    }

    void Logger::err(const std::string &msg) {
        Logger::log(msg, ERROR);
    }

    void Logger::dbg(const std::string &msg) {
#ifndef _DEBUG
        Logger::log(msg, DEBUG);
#endif
    }
}