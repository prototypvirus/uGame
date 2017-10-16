//
// Created by symbx on 16.10.17.
//

#include "game/TileObjectBlock.h"

uGame::TileObjectBlock::TileObjectBlock(uGame::TileObject *obj, sf::Texture *texture, sf::Uint8 x, sf::Uint8 y) :
    _vertex() {
    _object = obj;
    _texture = texture;
    _vertex.setPrimitiveType(sf::Triangles);
    _transform = sf::Transform(1, 0, x * 32,
                               0, 1, (y - (_object->Height-1)) * 32,
                               0, 0, 1);
    _frames = NULL;
    setState(0);
}

uGame::TileObjectBlock::~TileObjectBlock() {
    if(_frames != NULL)
        delete[] _frames;
}

void uGame::TileObjectBlock::setState(sf::Uint8 state) {
    if(state >= _object->StatesCount)
        state %= _object->StatesCount;
    _state = state;
    if(_frames != NULL)
        delete _frames;
    _frames = new FragmentData[_object->States[_state].FragmentsCount];
    _vertex.clear();
    _vertex.resize((size_t) (_object->States[_state].FragmentsCount * 6));
    for (sf::Uint8 i = 0; i < _object->States[_state].FragmentsCount; ++i) {
        _frames[i].Time = 0;
        _frames[i].Frame = 0;
        TileObjectFragment frag = _object->States[_state].Fragments[i];
        _vertex[i*6].position = sf::Vector2f(frag.PosX, frag.PosY);
        _vertex[i*6+1].position = sf::Vector2f(frag.PosX, frag.PosY+frag.Height);
        _vertex[i*6+2].position = sf::Vector2f(frag.PosX+frag.Width, frag.PosY);
        _vertex[i*6+3].position = sf::Vector2f(frag.PosX, frag.PosY+frag.Height);
        _vertex[i*6+4].position = sf::Vector2f(frag.PosX+frag.Width, frag.PosY);
        _vertex[i*6+5].position = sf::Vector2f(frag.PosX+frag.Width, frag.PosY+frag.Height);
        _updateFragment(i);
    }
}

void uGame::TileObjectBlock::update(float time) {
    for (int i = 0; i < _object->States[_state].FragmentsCount; ++i) {
        if(_object->States[_state].Fragments[i].FrameTime == 0)
            continue;
        _frames[i].Time += time;
        if(_frames[i].Time >= _object->States[_state].Fragments[i].FrameTime) {
            _frames[i].Time -= _object->States[_state].Fragments[i].FrameTime;
            _frames[i].Frame++;
            if(_frames[i].Frame >= _object->States[_state].Fragments[i].FramesCount)
                _frames[i].Frame = 0;
            _updateFragment(i);
        }
    }
}

void uGame::TileObjectBlock::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= _transform;
    states.texture = _texture;
    target.draw(_vertex, states);
}

void uGame::TileObjectBlock::_updateFragment(int i) {
    TileObjectFragment frag = _object->States[_state].Fragments[i];
    int tX = (frag.Frames[_frames[i].Frame]%32)*32;
    int tY = (frag.Frames[_frames[i].Frame]/32)*32;
    _vertex[i*6].texCoords = sf::Vector2f(tX, tY);
    _vertex[i*6+1].texCoords = sf::Vector2f(tX, tY+frag.Height);
    _vertex[i*6+2].texCoords = sf::Vector2f(tX+frag.Width, tY);
    _vertex[i*6+3].texCoords = sf::Vector2f(tX, tY+frag.Height);
    _vertex[i*6+4].texCoords = sf::Vector2f(tX+frag.Width, tY);
    _vertex[i*6+5].texCoords = sf::Vector2f(tX+frag.Width, tY+frag.Height);
}
