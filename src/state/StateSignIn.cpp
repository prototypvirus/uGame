//
// Created by symbx on 27.08.17.
//

#include "state/StateSignIn.h"
#include "core/Application.h"

namespace uGame {

    StateSignIn::StateSignIn() {}

    StateSignIn::~StateSignIn() {
        delete _bgTexture;
        delete _bg;
    }

    void StateSignIn::init(const Application *app) {
        _app = const_cast<Application *>(app);
        _bgTexture = new sf::Texture();
        sf::InputStream *stream = AssetsManager::getStream("/imgs/ui/main_bg.jpg");
        _bgTexture->loadFromStream(*stream);
        _bg = new sf::Sprite();
        _bg->setTexture(*_bgTexture);
        delete stream;
        centerContent(app->window()->getSize());
    }

    void StateSignIn::event(const sf::Event &event) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                _app->state()->close();
        }
    }

    void StateSignIn::update(const float time) {

    }

    void StateSignIn::draw(sf::RenderWindow &render) {
        render.draw(*_bg);
    }

    void StateSignIn::centerContent(sf::Vector2u wsize) {
        sf::FloatRect bgsize = _bg->getLocalBounds();
        _bg->setOrigin(bgsize.width/2, bgsize.height/2);
        _bg->setPosition(wsize.x/2, wsize.y/2);
        float ratio = bgsize.width/bgsize.height;
        if((wsize.x/wsize.y) >= ratio) {
            _bg->setScale((bgsize.height/wsize.y)*ratio, bgsize.height/wsize.y);
        }else{
            _bg->setScale(bgsize.width/wsize.x, (bgsize.width/wsize.x)*ratio);
        }
    }
}