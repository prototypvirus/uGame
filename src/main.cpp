#include "utils/Utils.h"
#include "utils/Logger.h"
#include "core/Application.h"

int main() {
    std::string appDir = uGame::Utils::getHome();
    uGame::Utils::prepareDirectory(appDir);
    uGame::Logger::init(appDir);
    uGame::L_INFO("Applicatio dir: "+appDir);
    uGame::Application app(appDir);
    app.run();
    uGame::Logger::clean();
    return 0;
}