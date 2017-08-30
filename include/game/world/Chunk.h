//
// Created by symbx on 29.08.17.
//

#ifndef UGAME_CHUNK_H
#define UGAME_CHUNK_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <core/Application.h>

namespace uGame {
    class Chunk : public sf::Drawable {
    public:
        Chunk(Application *app, sf::Uint32 world, sf::Uint32 layer, sf::Uint32 x, sf::Uint32 y);

        virtual ~Chunk();

        bool event(const sf::Event& event);

        void update(const float time);

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    };
}

#endif //UGAME_CHUNK_H
