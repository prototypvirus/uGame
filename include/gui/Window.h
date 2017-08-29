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
#include "UI.h"

namespace uGame {

    class Window : public ControlsContainer {
    public:
        Window(const sf::String &title);
        ~Window();

        bool event(const sf::Event &event) override;

        void update(const float time) override;

        sf::FloatRect getLocalBounds() const;

        sf::FloatRect getGlobalBounds() const;

        bool isClose();

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    private:
        sf::Texture _texture;
        sf::VertexArray _vertex;
        sf::Text _title;
        sf::Vector2f _size;
        Layout* _layout;
        bool _close;
        bool _press;
    };
}

#endif //UGAME_WINDOW_H
