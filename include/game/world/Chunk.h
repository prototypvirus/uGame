//
// Created by symbx on 29.08.17.
//

#ifndef UGAME_CHUNK_H
#define UGAME_CHUNK_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <core/Application.h>
#include <game/Tile.h>
#include <game/TileBlock.h>
#include <game/TileObject.h>
#include <game/TileObjectBlock.h>
#include <Constants.h>

namespace uGame {
    class Chunk : public sf::Drawable {
    public:
        Chunk(Application *app, sf::Uint32 world, sf::Uint32 layer, sf::Uint32 x, sf::Uint32 y);

        virtual ~Chunk();

        bool event(const sf::Event& event);

        void update(const float time);

        void load(int world, int layer, int x, int y);

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    private:
        Application* _app;
        std::vector<sf::Texture> _images;
        std::vector<Tile*> _tiles;
        TileBlock* _tilesMap[MAP_LAYER_TILES];
        bool _solidMap[MAP_LAYER_TILES];
        sf::View _view;
        std::vector<sf::Vertex> _vertex;
        std::vector<TileObject*> _objects;
        TileObjectBlock* _objectMap[MAP_TILES_COUNT];
        sf::FloatRect _calcView(int w, int h);
    };
}

#endif //UGAME_CHUNK_H
