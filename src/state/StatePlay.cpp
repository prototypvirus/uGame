//
// Created by symbx on 29.08.17.
//

#include "state/StatePlay.h"

namespace uGame {

    StatePlay::StatePlay() {}

    StatePlay::~StatePlay() {

    }

    void StatePlay::init(const Application *app) {
        _app = const_cast<Application *>(app);
    }

    void StatePlay::event(const sf::Event &event) {

    }

    void StatePlay::update(const float time) {

    }

    void StatePlay::draw(sf::RenderWindow &render) {

    }
}