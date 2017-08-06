#include "utils/Utils.h"
#include "utils/Logger.h"
#include "core/Application.h"

int main() {
    std::string appDir = Utils::getHome();
    Utils::prepareDirectory(appDir);
    Logger::init(appDir);
    Application app(appDir);
    app.run();
    Logger::clean();
    return 0;
}