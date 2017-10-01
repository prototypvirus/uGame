//
// Created by symbx on 05.08.17.
//

#ifndef UGAME_APPLICATION_H
#define UGAME_APPLICATION_H

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "AssetsManager.h"
#include "StateManager.h"
#include "Config.h"

namespace uGame {

    /**
     * Main application class
     */
    class Application {
    public:
        /**
         * Constructor
         * @param appDir - path to user home dir + .<gamename>
         */
        Application(const std::string &appDir);

        ~Application();

        /**
         * Start main loop
         */
        void run();

        /**
         * Mark loop to exit next cycle
         */
        void quit() const;

        /**
         * Get states manager
         * @return pointer to states manager
         */
        StateManager *state() const;

        /**
         * Get game window
         * @return pointer to main window
         */
        sf::RenderWindow *window() const;

        /**
         * Get configuration
         * @return pointer to configuration object
         */
        Config *config() const;

    protected:
        StateManager *_state;
        sf::RenderWindow *_window;
        Config *_cfg;
        sf::Clock _clock;
        bool _running;

        /**
         * Main loop
         */
        void loop();
    };
}

#endif //UGAME_APPLICATION_H
