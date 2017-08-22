//
// Created by symbx on 08.08.17.
//

#include <SFML/Graphics/Sprite.hpp>
#include <utils/Logger.h>
#include "state/StateMenu.h"
#include "core/StateManager.h"
#include "core/Application.h"

namespace uGame {

    StateMenu::StateMenu() {}

    StateMenu::~StateMenu() {
        delete _bgTexture;
        delete _bg;
        delete _menuFrame;
    }


    void StateMenu::init(const Application *app) {
        _app = const_cast<Application *>(app);
        _bgTexture = new sf::Texture();
        sf::InputStream *stream = AssetsManager::getStream("/imgs/ui/bg.png");
        _bgTexture->loadFromStream(*stream);
        _bgTexture->setRepeated(true);
        _bg = new sf::RectangleShape();
        _bg->setTexture(_bgTexture);
        _bg->setPosition(0, 0);
        sf::Vector2u wsize = app->window()->getSize();
        _bg->setTextureRect(sf::IntRect(0, 0, wsize.x, wsize.y));
        _bg->setSize(sf::Vector2f(wsize.x, wsize.y));
        delete stream;
        _menuFrame = new Window(L"MENU");
        centerContent(app->window()->getSize());
    }

    void StateMenu::event(const sf::Event &event) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                _app->state()->close();
        }
        if (event.type == sf::Event::Resized) {
            sf::Vector2u wsize(event.size.width, event.size.height);
            _bg->setTextureRect(sf::IntRect(0, 0, wsize.x, wsize.y));
            _bg->setSize(sf::Vector2f(wsize.x, wsize.y));
            centerContent(wsize);
        }
    }

    void StateMenu::update(const float time) {

    }

    void StateMenu::draw(sf::RenderWindow &render, const float time) {
        render.draw(*_bg);
        render.draw(*_menuFrame);
    }

    void StateMenu::centerContent(sf::Vector2u wsize) {
        sf::Vector2u fsize = _menuFrame->getSize();
        _menuFrame->setPosition((wsize.x-fsize.x)/2, (wsize.y-fsize.y)/2);
    }
}