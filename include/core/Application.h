//
// Created by symbx on 05.08.17.
//

#ifndef UGAME_APPLICATION_H
#define UGAME_APPLICATION_H

#include <string>

class Application {
public:
    Application(const std::string& appDir);
    ~Application();
    void run();
};


#endif //UGAME_APPLICATION_H
