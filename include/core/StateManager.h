//
// Created by symbx on 08.08.17.
//

#ifndef UGAME_STATEMANAGER_H
#define UGAME_STATEMANAGER_H


#include "GameState.h"

namespace uGame {

    class Application;

    /**
     * States manager
     */
    class StateManager {
    public:
        /**
         * Constructor
         * @param app - pointer to main application object
         */
        StateManager(Application *app);

        ~StateManager();

        /**
         * Initialize
         */
        void init();

        /**
         * Cleanup
         */
        void clean();

        /**
         * Pause current, initialize and open given state
         * @param state - new state of application
         */
        void open(GameState *state);

        /**
         * Remove current, initialize and open given state
         * @param state - new state of application
         */
        void replace(GameState *state);

        /**
         * Close current state and resume paused if exists (if not - quit)
         */
        void close();

        /**
         * Handle events (send to current state)
         * @param event - event object
         */
        void event(const sf::Event &event);

        /**
         * Handle updates (send to current state)
         * @param time - time elapsed from last update
         */
        void update(const float time);

        /**
         * Handle draw (send to current state)
         * @param render - main application windpw
         */
        void draw(sf::RenderWindow &render);

    protected:
        Application *_app;
        std::vector<GameState *> _states;
    };
}

#endif //UGAME_STATEMANAGER_H
