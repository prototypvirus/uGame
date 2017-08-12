//
// Created by symbx on 05.08.17.
//

#include <Constants.h>
#include "core/Application.h"
#include "utils/Logger.h"

namespace uGame {

    Application::Application(const std::string &appDir) :
            _clock() {
        AssetsManager::init(appDir);
        _state = new StateManager(this);
        sf::VideoMode mode = sf::VideoMode::getDesktopMode();
        sf::Uint32 width = WIN_WIDTH;
        sf::Uint32 height = WIN_HEIGHT;
        if (width > mode.width)
            width = mode.width;
        if (height > mode.height)
            height = mode.height;
        _window = new sf::RenderWindow(sf::VideoMode(width, height), GAME_NAME, sf::Style::Default);
        _window->setFramerateLimit(FIX_FPS);
        _running = false;
    }

    Application::~Application() {
        delete _window;
        AssetsManager::destroy();
    }

    void Application::run() {
        if (_running)
            return;
        loop();
    }

    void Application::loop() {
        _running = true;
        _state->init();
        while (_window->isOpen()) {
            sf::Event event;
            while (_window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    _window->close();
                if (event.type == sf::Event::Resized) {
                    sf::Vector2u size = sf::Vector2u(event.size.width, event.size.height);
                    bool min = false;
                    if (size.x < WIN_MIN_WIDTH) {
                        size.x = WIN_MIN_WIDTH;
                        min = true;
                    }
                    if (size.y < WIN_MIN_HEIGHT) {
                        size.y = WIN_MIN_HEIGHT;
                        min = true;
                    }
                    if (min)
                        _window->setSize(size);
                    else
                        _window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                }
                _state->event(event);
            }
            float time = _clock.restart().asSeconds();
            _state->update(time);
            _window->clear(sf::Color::Black);
            _state->draw(*_window, time);
            _window->display();
        }
    }

    void Application::quit() const {
        _window->close();
    }

    StateManager *Application::state() const {
        return _state;
    }

    sf::RenderWindow *Application::window() const {
        return _window;
    }

}