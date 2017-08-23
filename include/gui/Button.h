//
// Created by symbx on 22.08.17.
//

#ifndef UGAME_BUTTON_H
#define UGAME_BUTTON_H

#include <functional>
#include <gui/Control.h>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace uGame {
    class Button : public Control {
    public:
        Button(const sf::String &text);

        virtual ~Button();

        void setVisible(bool v) override;

        bool isVisible() override;

        bool isPress();

        void event(const sf::Event &event) override;

        void update(const float time) override;

        sf::FloatRect getLocalBounds() const;

        sf::FloatRect getGlobalBounds() const;

    protected:
        enum State {
            Normal,
            Hover,
            Press
        };
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        void setState(State state);
        bool _visible;
        State _state;
        sf::Vector2f _size;
        sf::Texture _texture;
        sf::VertexArray _vertex;
        sf::Text _text;
    };
}

#endif //UGAME_BUTTON_H
