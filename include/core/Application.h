//
// Created by symbx on 05.08.17.
//

#ifndef UGAME_APPLICATION_H
#define UGAME_APPLICATION_H

#include <string>
#include "AssetsManager.h"

class Application {
public:
    Application(const std::string& appDir);
    ~Application();
    void run();

protected:
    AssetsManager* _assets;
};


#endif //UGAME_APPLICATION_H
