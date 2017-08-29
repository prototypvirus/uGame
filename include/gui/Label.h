//
// Created by symbx on 25.08.17.
//

#ifndef UGAME_LABEL_H
#define UGAME_LABEL_H

#include "Control.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

namespace uGame {
    class Label : public Control {
    public:

        Label(const sf::String &text, unsigned int width);

        virtual ~Label();

        bool event(const sf::Event &event) override;

        void update(const float time) override;

        void setText(const sf::String& text);

        void setColor(const sf::Color& color);

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        sf::Text _text;
        Layout* _layout;
        unsigned int _width;
    };
}

#endif //UGAME_LABEL_H
