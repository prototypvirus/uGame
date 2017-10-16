//
// Created by symbx on 16.10.17.
//

#ifndef UGAME_TILE_H
#define UGAME_TILE_H

#include <SFML/Config.hpp>

namespace uGame {
    struct Tile {
        float frameTime;
        sf::Uint16* frames;
        sf::Uint8 framesCount;
    };
}

#endif //UGAME_TILE_H
