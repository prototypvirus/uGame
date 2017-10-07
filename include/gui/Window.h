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
    /**
     * In-Game window
     */
    class Window : public ControlsContainer {
    public:
        /**
         * Constructor
         * @param title - title of window
         */
        Window(const sf::String &title);
        ~Window();

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
         * If user click close button on window
         * @return clicked
         */
        bool isClose();

    protected:
        /**
         * Draw button
         * @param target - renderer
         * @param states - states (textures, colors, etc.)
         */
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
