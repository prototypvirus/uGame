//
// Created by symbx on 08.08.17.
//

#ifndef UGAME_STATELOADING_H
#define UGAME_STATELOADING_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Thread.hpp>
#include <core/GameState.h>
#include "core/Application.h"

namespace uGame {

    /**
     * Loading state (init loading of game)
     */
    class StateLoading : public GameState {
    public:
        /**
         * Constructor
         */
        StateLoading();

        ~StateLoading();

        /**
         * Initialize (instead constructor)
         * @param app - pointer to main application object
         */
        void init(const Application *app) override;

        /**
         * Handle event
         * @param event - event object
         */
        void event(const sf::Event &event) override;

        /**
         * Handle updates
         * @param time - time from previous update
         */
        void update(const float time) override;

        /**
         * Handle draws
         * @param render - pointer to main window (renderer)
         */
        void draw(sf::RenderWindow &render) override;

    private:
        sf::Sprite *_logo;
        sf::Text *_loadText;
        sf::Texture *_logoTexture;
        sf::RectangleShape *_progressBack;
        sf::RectangleShape *_progress;
        sf::Font *_font;

        /**
         * Center elements of window
         * @param wsize - game window size
         */
        void centerContent(sf::Vector2u wsize);

        /**
         * Center text of window
         * @param wsize - game window size
         */
        void centerText(sf::Vector2u wsize);

        bool _progressVisible;

        /**
         * Set progress of loading
         * @param val - progress (0-100)
         */
        void setProgress(float val);

        /**
         * Set text of loading (state)
         * @param msg - text to set
         */
        void setText(const std::string &msg);

        sf::Thread *_work;
        Application *_app;
    };
}

#endif //UGAME_STATELOADING_H
