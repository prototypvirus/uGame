//
// Created by symbx on 16.10.17.
//

#ifndef UGAME_TILEOBJECT_H
#define UGAME_TILEOBJECT_H

#include <SFML/Config.hpp>

namespace uGame {
    struct TileObject {
        struct TileObjectState* States;
        sf::Uint8 StatesCount;
        sf::Uint8 Image;
        sf::Uint8 Width;
        sf::Uint8 Height;
    };
    struct TileObjectState {
        struct TileObjectFragment* Fragments;
        sf::Uint8 FragmentsCount;
        sf::Int8 InteractX;
        sf::Int8 InteractY;
    };
    struct TileObjectFragment {
        float FrameTime;
        sf::Uint16* Frames;
        sf::Uint8 FramesCount;
        //RAW SIZE NOT NEED TO MULTIPLY 32
        sf::Uint8 PosX;
        sf::Uint8 PosY;
        sf::Uint8 Width;
        sf::Uint8 Height;
    };
}

#endif //UGAME_TILEOBJECT_H
