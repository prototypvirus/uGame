//
// Created by symbx on 08.08.17.
//

#ifndef UGAME_STATEMENU_H
#define UGAME_STATEMENU_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <core/GameState.h>
#include <gui/Window.h>
#include <gui/Button.h>
#include <gui/Label.h>

namespace uGame {

    class Application;

    /**
     * State of app main menu
     */
    class StateMenu : public GameState {
    public:
        /**
         * Constructor
         */
        StateMenu();

        ~StateMenu();

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
        Application *_app;
        sf::Texture _bgTexture;
        sf::Sprite _bg;
        Window* _menuFrame;
        Button* _playBtn;
        Button* _profBtn;
        Button* _optsBtn;
        Button* _exitBtn;
        Label* _profile;

        /**
         * Center elements of window
         * @param wsize - game window size
         */
        void centerContent(sf::Vector2u wsize);
    };
}

#endif //UGAME_STATEMENU_H
