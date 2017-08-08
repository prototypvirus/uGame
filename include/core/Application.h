//
// Created by symbx on 05.08.17.
//

#ifndef UGAME_APPLICATION_H
#define UGAME_APPLICATION_H

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "AssetsManager.h"

class Application {
public:
    Application(const std::string& appDir);
    ~Application();
    void run();

protected:
    AssetsManager* _assets;
    sf::RenderWindow* _window;
    sf::Clock _clock;
    bool _running;
    void loop();
};


#endif //UGAME_APPLICATION_H
