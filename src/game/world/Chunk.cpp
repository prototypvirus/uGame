//
// Created by symbx on 29.08.17.
//

#include <core/Application.h>
#include <cstring>
#include <utils/Logger.h>
#include "game/world/Chunk.h"

namespace uGame {

    Chunk::Chunk(Application *app, sf::Uint32 world, sf::Uint32 layer, sf::Uint32 x, sf::Uint32 y) :
            _images(),
            _tiles(),
            _objects(),
            _vertex(),
            _view() {
        _app = app;
        for (int i = 0; i < MAP_TILES_COUNT; ++i) {
            _objectMap[i] = NULL;
        }
        load(world, layer, x, y);
        sf::Vector2u sz = app->window()->getSize();
        const sf::FloatRect rect = _calcView(sz.x, sz.y);
        _view.reset(rect);
        //_view.setViewport(sf::FloatRect(0, 0, 1, 0.88));
        _view.setViewport(sf::FloatRect(0, 0, 1, 1));
    }

    Chunk::~Chunk() {
        for (int i = 0; i < _tiles.size(); ++i) {
            delete[] _tiles[i]->frames;
            delete _tiles[i];
        }
        for (int j = 0; j < _objects.size(); ++j) {
            for (int i = 0; i < _objects[j]->StatesCount; ++i) {
                for (int k = 0; k < _objects[j]->States[i].FragmentsCount; ++k) {
                    delete[] _objects[j]->States[i].Fragments[k].Frames;
                }
                delete[] _objects[j]->States[i].Fragments;
            }
            delete[] _objects[j]->States;
            delete _objects[j];
        }
        for (int i = 0; i < MAP_TILES_COUNT; ++i) {
            delete _tilesMap[i];
            if(_objectMap[i] != NULL)
                delete _objectMap[i];
        }
    }

    void Chunk::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        sf::View v = target.getView();
        target.setView(_view);
        states.texture = &_images[0];
        target.draw(&_vertex[0], _vertex.size(), sf::Triangles, states);
        for (int j = 0; j < MAP_TILES_COUNT; ++j) {
            if(_objectMap[j] != NULL) {
                target.draw(*_objectMap[j]);
            }
        }
        target.setView(v);
    }

    bool Chunk::event(const sf::Event &event) {
        if(event.type == sf::Event::Resized) {
            const sf::FloatRect rect = _calcView(event.size.width, event.size.height);
            _view.reset(rect);
        }
        if(event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Left:
                    _view.move(-10, 0);
                    break;
                case sf::Keyboard::Right:
                    _view.move(10, 0);
                    break;
                case sf::Keyboard::Up:
                    _view.move(0, -10);
                    break;
                case sf::Keyboard::Down:
                    _view.move(0, 10);
                    break;
            }
        }
    }

    void Chunk::update(const float time) {
        for (int i = 0; i < MAP_LAYER_TILES; ++i) {
            if(_tilesMap[i] != NULL && _tilesMap[i]->isAnimated() && _tilesMap[i]->update(time)) {
                int p = _tilesMap[i]->getPos()*6;
                _vertex[p] = _tilesMap[i]->getVertex()[0];
                _vertex[p+1] = _tilesMap[i]->getVertex()[1];
                _vertex[p+2] = _tilesMap[i]->getVertex()[2];
                _vertex[p+3] = _tilesMap[i]->getVertex()[1];
                _vertex[p+4] = _tilesMap[i]->getVertex()[2];
                _vertex[p+5] = _tilesMap[i]->getVertex()[3];
            }
        }
        for (int j = 0; j < MAP_TILES_COUNT; ++j) {
            if(_objectMap[j] != NULL)
                _objectMap[j]->update(time);
        }
    }

    void Chunk::load(int world, int layer, int x, int y) {
        sf::InputStream* mapStream = AssetsManager::getStream(
                "/world/dim-"+std::to_string(world)+
                "/lvl-"+std::to_string(layer)+
                '/'+std::to_string(x)+'x'+std::to_string(y)+".chk");

        //Images count
        sf::Uint8 imgsCount;
        mapStream->read(&imgsCount, 1);
        _images.reserve(imgsCount);
        //Buffer for image path
        char* buffer = new char[128];
        memset(buffer, 0, 128);
        for(sf::Uint8 i = 0; i < imgsCount; i++) {
            //Read path
            sf::Uint8 nameLen;
            mapStream->read(&nameLen, 1);
            mapStream->read(buffer, nameLen);
            std::string name;
            name.assign(buffer, nameLen);
            //Load texture
            sf::Texture texture;
            sf::InputStream* textureStream = AssetsManager::getStream(name);
            texture.loadFromStream(*textureStream);
            delete textureStream;
            _images.push_back(texture);
            //cleanup
            memset(buffer, 0, 128);
        }
        delete[] buffer;

        //Tiles count
        sf::Uint16 tilesCount;
        mapStream->read(&tilesCount, 2);
        _tiles.reserve(tilesCount);
        for(sf::Uint16 i = 0; i < tilesCount; i++) {
            Tile* tile = new Tile();
            mapStream->read(&tile->frameTime, 4); //Time
            mapStream->read(&tile->framesCount, 1); //Count
            tile->frames = new sf::Uint16[tile->framesCount]; //Prepare array
            for (sf::Uint8 j = 0; j < tile->framesCount; ++j) {
                mapStream->read(&tile->frames[j], 2); //Read frames
            }
            _tiles.push_back(tile);
        }

        //TODO: Optimize x,y loop -> one loop (y*size+x)
        //Reserve only for one layer
        _vertex.reserve(MAP_TILES_COUNT*6);
        //Read layer 1
        sf::Uint16 vPos = 0;
        for (sf::Uint8 ty = 0; ty < MAP_SIZE; ++ty) {
            for (sf::Uint8 tx = 0; tx < MAP_SIZE; ++tx) {
                sf::Int16 tileId;
                mapStream->read(&tileId, 2);
                if(tileId >= 0) {
                    TileBlock* bl = new TileBlock(_tiles[tileId], tx, ty);
                    _tilesMap[ty * MAP_SIZE + tx] = bl;
                    bl->setPos(vPos); // TODO: May be bl->setPos(vPos++);
                    _vertex.push_back(bl->getVertex()[0]);
                    _vertex.push_back(bl->getVertex()[1]);
                    _vertex.push_back(bl->getVertex()[2]);
                    _vertex.push_back(bl->getVertex()[1]);
                    _vertex.push_back(bl->getVertex()[2]);
                    _vertex.push_back(bl->getVertex()[3]);
                    vPos++;
                } else
                    _tilesMap[ty*MAP_SIZE+tx] = NULL;
            }
        }

        //Read layer 2
        for (sf::Uint8 ty = 0; ty < MAP_SIZE; ++ty) {
            for (sf::Uint8 tx = 0; tx < MAP_SIZE; ++tx) {
                sf::Int16 tileId;
                mapStream->read(&tileId, 2);
                if(tileId >= 0) {
                    TileBlock* bl = new TileBlock(_tiles[tileId], tx, ty);
                    _tilesMap[MAP_TILES_COUNT + (ty * MAP_SIZE + tx)] = bl;
                    bl->setPos(vPos); // TODO: May be bl->setPos(vPos++);
                    _vertex.push_back(bl->getVertex()[0]);
                    _vertex.push_back(bl->getVertex()[1]);
                    _vertex.push_back(bl->getVertex()[2]);
                    _vertex.push_back(bl->getVertex()[1]);
                    _vertex.push_back(bl->getVertex()[2]);
                    _vertex.push_back(bl->getVertex()[3]);
                    vPos++;
                } else
                    _tilesMap[MAP_TILES_COUNT+(ty*MAP_SIZE+tx)] = NULL;
            }
        }
        _vertex.shrink_to_fit();

        // TODO: Read solidity map
        sf::Uint8 tmp;
        for (int m = 0; m < MAP_SIZE; ++m) {
            for (int i = 0; i < MAP_SIZE; ++i) {
                mapStream->read(&tmp, 1);
                _solidMap[m*MAP_SIZE+i] = tmp;
            }
        }

        sf::Uint16 objCount;
        mapStream->read(&objCount, 2);

        _objects.reserve(objCount);
        for (int k = 0; k < objCount; ++k) {
            TileObject* o = new TileObject();
            mapStream->read(&o->Image, 1);
            mapStream->read(&o->Width, 1);
            mapStream->read(&o->Height, 1);
            mapStream->read(&o->StatesCount, 1);
            o->States = new TileObjectState[o->StatesCount];
            for (int i = 0; i < o->StatesCount; ++i) {
                o->States[i] = TileObjectState();
                mapStream->read(&o->States[i].InteractX, 1);
                mapStream->read(&o->States[i].InteractY, 1);
                mapStream->read(&o->States[i].FragmentsCount, 1);
                o->States[i].Fragments = new TileObjectFragment[o->States[i].FragmentsCount];
                for (int j = 0; j < o->States[i].FragmentsCount; ++j) {
                    o->States[i].Fragments[j] = TileObjectFragment();
                    mapStream->read(&o->States[i].Fragments[j].FrameTime, 4);
                    mapStream->read(&o->States[i].Fragments[j].PosX, 1);
                    mapStream->read(&o->States[i].Fragments[j].PosY, 1);
                    mapStream->read(&o->States[i].Fragments[j].Width, 1);
                    mapStream->read(&o->States[i].Fragments[j].Height, 1);
                    mapStream->read(&o->States[i].Fragments[j].FramesCount, 1);
                    o->States[i].Fragments[j].Frames = new sf::Uint16[o->States[i].Fragments[j].FramesCount];
                    for (int l = 0; l < o->States[i].Fragments[j].FramesCount; ++l) {
                        mapStream->read(&o->States[i].Fragments[j].Frames[l], 2);
                    }
                }
            }
            _objects.push_back(o);
        }
        L_INFO("Loaded objects: "+std::to_string(_objects.size()));

        for (sf::Uint8 m = 0; m < MAP_SIZE; ++m) {
            for (sf::Uint8 i = 0; i < MAP_SIZE; ++i) {
                sf::Int16 id;
                mapStream->read(&id, 2);
                if(id >= 0) {
                    TileObjectBlock* ob = new TileObjectBlock(_objects[id], &_images[_objects[id]->Image], i, m);
                    _objectMap[m*MAP_SIZE+i] = ob;
                }
            }
        }

        delete mapStream;
    }

    sf::FloatRect Chunk::_calcView(int w, int h) {
        // TODO: Move 0.88 to constants header
        sf::FloatRect out(0, 0, 1, 1);
        if(w > 1024 || h > 1024) {
            if(w > h) {
                out.width = 1024;
                out.height = (h/(float)w)*1024;
                //out.height = ((h*0.88f)/(float)w)*1024;
            } else {
                out.height = h;
                out.width = (w/(float)h)*1024;
                //out.height = h*0.88f;
                //out.width = (w/(h*0.88f))*1024;
            }
            return out;
        }
        out.width = w;
        out.height = h;
        //out.height = h*0.88f;
        return out;
    }
}