//
// Created by symbx on 28.08.17.
//

#ifndef UGAME_INPUTBOX_H
#define UGAME_INPUTBOX_H

#include <SFML/System/String.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "UI.h"
#include "Control.h"

namespace uGame {
    class InputBox : public Control {
    public:
        enum Range {
            Normal,
            Numeric,
            Latin,
            LatinNoNumeric
        };

        InputBox(int width);

        virtual ~InputBox();

        bool event(const sf::Event &event) override;

        void update(const float time) override;

        void setText(const sf::String& str);

        const sf::String& getText() const;

        sf::FloatRect getLocalBounds() const;

        sf::FloatRect getGlobalBounds() const;

        void setCharacterRange(Range r);

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        void setCursor(int pos);
        int getCursor();
        bool checkRange(sf::Uint32 chr);

        Layout* _layout;
        sf::Text _text;
        sf::VertexArray _vertex;
        sf::RectangleShape _cursor;
        int _cursorPos;
        int _maxLength;
        float _tick;
        int _width;
        Range _range;
    };
}

#endif //UGAME_INPUTBOX_H
