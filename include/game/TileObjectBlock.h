//
// Created by symbx on 16.10.17.
//

#ifndef UGAME_TILEOBJECTBLOCK_H
#define UGAME_TILEOBJECTBLOCK_H

#include <SFML/Graphics/Texture.hpp>
#include <game/TileObject.h>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace uGame {
    class TileObjectBlock : public sf::Drawable {
    public:
        struct FragmentData {
            float Time;
            sf::Uint8 Frame;
        };
        TileObjectBlock(TileObject* obj, sf::Texture* texture, sf::Uint8 x, sf::Uint8 y);
        ~TileObjectBlock();
        void setState(sf::Uint8 state);
        void update(float time);

    private:
        TileObject* _object;
        sf::Uint8 _state;
        FragmentData* _frames;
        sf::Texture* _texture;
        sf::VertexArray _vertex;
        sf::Transform _transform;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void _updateFragment(int i);
    };
}

#endif //UGAME_TILEOBJECTBLOCK_H
