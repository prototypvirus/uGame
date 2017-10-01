//
// Created by symbx on 08.08.17.
//

#ifndef UGAME_GAMESTATE_H
#define UGAME_GAMESTATE_H

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace uGame {

    class Application;

    /**
     * State of application
     */
    class GameState {
    public:
        /**
         * Initialize (instead constructor)
         * @param app - pointer to main application object
         */
        virtual void init(const Application *app) = 0;

        /**
         * Handle event
         * @param event - event object
         */
        virtual void event(const sf::Event &event) = 0;

        /**
         * Handle updates
         * @param time - time from previous update
         */
        virtual void update(const float time) = 0;

        /**
         * Handle draws
         * @param render - pointer to main window (renderer)
         */
        virtual void draw(sf::RenderWindow &render) = 0;

    };
}

#endif //UGAME_GAMESTATE_H
