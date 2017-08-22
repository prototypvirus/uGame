//
// Created by symbx on 12.08.17.
//

#ifndef UGAME_WINDOW_H
#define UGAME_WINDOW_H

#include "ControlsContainer.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace uGame {

    class Window : public ControlsContainer {
    public:
        Window(const std::wstring &title);
        ~Window();
        void setPosition(sf::Vector2u pos);
        void setPosition(sf::Uint32 x, sf::Uint32 y);
        sf::Vector2u getPosition();
        void setSize(sf::Vector2u size);
        void setSize(sf::Uint32 w, sf::Uint32 h);
        sf::Vector2u getSize();

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    private:
        sf::Texture _texture;
        sf::Vector2u _pos;
        sf::Transform _transform;
        sf::Vector2u _size;
        sf::VertexArray _vertex;
        sf::Text _title;
    };
}

#endif //UGAME_WINDOW_H
