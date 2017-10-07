//
// Created by symbx on 25.08.17.
//

#ifndef UGAME_LABEL_H
#define UGAME_LABEL_H

#include "Control.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

namespace uGame {
    /**
     * Static-text control
     */
    class Label : public Control {
    public:
        /**
         * Constructor
         * @param text - text to display
         * @param width - width of control (px)
         */
        Label(const sf::String &text, unsigned int width);

        virtual ~Label();

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
         * Set text of label
         * @param text - text to set
         */
        void setText(const sf::String& text);

        /**
         * Set color of text
         * @param color - color to set
         */
        void setColor(const sf::Color& color);

    protected:
        /**
         * Draw button
         * @param target - renderer
         * @param states - states (textures, colors, etc.)
         */
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        sf::Text _text;
        Layout* _layout;
        unsigned int _width;
    };
}

#endif //UGAME_LABEL_H
