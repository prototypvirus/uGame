//
// Created by symbx on 29.08.17.
//

#ifndef UGAME_STATEPLAY_H
#define UGAME_STATEPLAY_H

#include <core/GameState.h>
#include <SFML/Graphics/RenderWindow.hpp>

namespace uGame {
    /**
     * Playing game
     */
    class StatePlay : public GameState {
    public:
        StatePlay();

        virtual ~StatePlay();

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

    protected:
        Application* _app;
    };
}

#endif //UGAME_STATEPLAY_H
