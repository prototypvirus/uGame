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

    /**
     * Gui button
     */
    class Button : public Control {
    public:
        /**
         * Constructor
         * @param text - text for button
         */
        Button(const sf::String &text);

        virtual ~Button();

        /**
         * is button was pressed
         * @return pressed?
         */
        bool isPress();

        /**
         * Handle events
         * @param event - events object
         * @return handled (if true do not send to next control)
         */
        bool event(const sf::Event &event) override;

        /**
         * Handle updates
         * @param time  - time elapsed from last update
         */
        void update(const float time) override;

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
         * Set text on button
         * @param text - text to set
         */
        void setText(const sf::String& text);

    protected:
        /**
         * Available states
         */
        enum State {
            Normal,
            Hover,
            Press
        };

        /**
         * Draw button
         * @param target - renderer
         * @param states - states (textures, colors, etc.)
         */
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        /**
         * Set state of button
         * @param state - new state
         */
        void setState(State state);
        bool _visible;
        bool _press;
        State _state;
        sf::Vector2f _size;
        sf::Texture _texture;
        sf::VertexArray _vertex;
        sf::Text _text;
        Layout* _layout;
    };
}

#endif //UGAME_BUTTON_H
