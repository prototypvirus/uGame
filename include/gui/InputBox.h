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
    /**
     * Control for user enter data
     */
    class InputBox : public Control {
    public:
        /**
         * Char ranges
         */
        enum Range {
            Normal,
            Numeric,
            Latin,
            LatinNoNumeric
        };

        /**
         * Constructor
         * @param width - width of input (px)
         */
        InputBox(int width);

        virtual ~InputBox();

        /**
         * Handle events
         * @param event - event object
         * @return event handled (if true do not send next control)
         */
        bool event(const sf::Event &event) override;

        /**
         * Handle updates
         * @param time - time elapsed from last update
         */
        void update(const float time) override;

        /**
         * Set data of control
         * @param str - data to set
         */
        void setText(const sf::String& str);

        /**
         * Get data of control
         * @return data of control
         */
        const sf::String& getText() const;

        /**
         * Get button bounds (local - position is 0x0)
         * @return rectangle of button
         */
        sf::FloatRect getLocalBounds() const;

        /**
         * Get button bounds (with position)
         * @return rectangle of button
         */
        sf::FloatRect getGlobalBounds() const;

        /**
         * Set range of allowed characters
         * @param r - allowed range
         */
        void setCharacterRange(Range r);

        /**
         * Return if user press enter
         * @return pressed enter
         */
        bool isReturn();

    protected:
        /**
         * Draw button
         * @param target - renderer
         * @param states - states (textures, colors, etc.)
         */
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        /**
         * Set position of input cursor
         * @param pos - new position
         */
        void setCursor(int pos);

        /**
         * Get current position of input cursor
         * @return - current position
         */
        int getCursor();

        /**
         * Check if given character in allowed range
         * @param chr - character to check
         * @return character in allowed range
         */
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
        bool _return;
    };
}

#endif //UGAME_INPUTBOX_H
