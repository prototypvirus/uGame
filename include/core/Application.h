//
// Created by symbx on 05.08.17.
//

#ifndef UGAME_APPLICATION_H
#define UGAME_APPLICATION_H

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "AssetsManager.h"
#include "StateManager.h"

class Application {
public:
    Application(const std::string& appDir);
    ~Application();
    void run();
    void quit() const;
    AssetsManager* assets() const;
    StateManager* state() const;
    sf::RenderWindow* window() const;

protected:
    AssetsManager* _assets;
    StateManager* _state;
    sf::RenderWindow* _window;
    sf::Clock _clock;
    bool _running;
    void loop();
};


#endif //UGAME_APPLICATION_H
