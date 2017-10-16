//
// Created by symbx on 16.10.17.
//

#ifndef UGAME_TILEBLOCK_H
#define UGAME_TILEBLOCK_H

#include <SFML/Graphics/VertexArray.hpp>
#include "Tile.h"

namespace uGame {
    class TileBlock {
    public:
        TileBlock(Tile* tile, sf::Uint8 x, sf::Uint8 y);
        bool isAnimated();
        bool update(float time);
        sf::VertexArray& getVertex();
        sf::Uint16 getPos();
        void setPos(sf::Uint16 p);

    private:
        void _updateFrame();
        sf::VertexArray _vertex;
        Tile* _tile;
        float _time;
        sf::Uint16 _vertexPos;
        sf::Uint8 _frame;
    };
}

#endif //UGAME_TILEBLOCK_H
