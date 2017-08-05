//
// Created by symbx on 05.08.17.
//

#include "utils/Logger.h"

std::ofstream* Logger::_file;

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
    switch(severity)
    {
        case INFO:
            Logger::_file->write("[INFO] ", 7);
            break;
        case WARNING:
            Logger::_file->write("[WARNING] ", 10);
            break;
        case ERROR:
            Logger::_file->write("[ERROR] ", 8);
            break;
        case DEBUG:
            Logger::_file->write("[DEBUG] ", 8);
            break;
    }
    Logger::_file->write(msg.c_str(), msg.length());
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
//#ifndef DEBUG
    Logger::log(msg, DEBUG);
//#endif
}
