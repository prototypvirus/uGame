//
// Created by symbx on 29.08.17.
//

#include "state/StatePlay.h"

namespace uGame {

    StatePlay::StatePlay() {}

    StatePlay::~StatePlay() {
        delete _chunk;
    }

    void StatePlay::init(const Application *app) {
        _app = const_cast<Application *>(app);
        _chunk = new Chunk(_app, 0, 0, 0, 0);
    }

    void StatePlay::event(const sf::Event &event) {
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            _app->state()->close();
        if(_chunk != NULL)
            _chunk->event(event);
    }

    void StatePlay::update(const float time) {
        _chunk->update(time);
    }

    void StatePlay::draw(sf::RenderWindow &render) {
        render.draw(*_chunk);
    }
}