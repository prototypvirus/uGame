//
// Created by symbx on 05.08.17.
//

#include "core/Application.h"
#include "utils/Logger.h"

Application::Application(const std::string &appDir) {
    _assets = new AssetsManager(appDir);
}

Application::~Application() {
    delete _assets;
}

void Application::run() {
    _assets->run();
}
