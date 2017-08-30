//
// Created by symbx on 29.08.17.
//

#include <core/Application.h>
#include "game/world/Chunk.h"

namespace uGame {

    Chunk::Chunk(Application *app, sf::Uint32 world, sf::Uint32 layer, sf::Uint32 x, sf::Uint32 y) {}

    Chunk::~Chunk() {

    }

    void Chunk::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    }

    bool Chunk::event(const sf::Event &event) {
        return false;
    }

    void Chunk::update(const float time) {

    }
}