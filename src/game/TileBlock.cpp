//
// Created by symbx on 16.10.17.
//

#include "game/TileBlock.h"

namespace uGame {
    TileBlock::TileBlock(uGame::Tile *tile, sf::Uint8 x, sf::Uint8 y) :
            _vertex(sf::TrianglesStrip, 4) {
        _tile = tile;
        _time = 0;
        _frame = 0;
        int tmpX = (x * 32);
        int tmpY = (y * 32);
        _vertex[0].position = sf::Vector2f(tmpX, tmpY);
        _vertex[1].position = sf::Vector2f(tmpX, tmpY+32);
        _vertex[2].position = sf::Vector2f(tmpX+32, tmpY);
        _vertex[3].position = sf::Vector2f(tmpX+32, tmpY+32);
        _updateFrame();
    }

    bool TileBlock::isAnimated() {
        return _tile->frameTime != 0;
    }

    bool TileBlock::update(float time) {
        _time += time;
        if(_time >= _tile->frameTime) {
            _time -= _tile->frameTime;
            _frame++;
            if(_frame >= _tile->framesCount)
                _frame = 0;
            _updateFrame();
            return true;
        }
        return false;
    }

    sf::VertexArray &TileBlock::getVertex() {
        return _vertex;
    }

    sf::Uint16 TileBlock::getPos() {
        return _vertexPos;
    }

    void TileBlock::setPos(sf::Uint16 p) {
        _vertexPos = p;
    }

    void TileBlock::_updateFrame() {
        int tmpX = (_tile->frames[_frame] % 32)*32;
        int tmpY = (_tile->frames[_frame] / 32)*32;
        _vertex[0].texCoords = sf::Vector2f(tmpX, tmpY);
        _vertex[1].texCoords = sf::Vector2f(tmpX, tmpY+32);
        _vertex[2].texCoords = sf::Vector2f(tmpX+32, tmpY);
        _vertex[3].texCoords = sf::Vector2f(tmpX+32, tmpY+32);
    }
}