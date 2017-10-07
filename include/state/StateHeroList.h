//
// Created by symbx on 01.10.17.
//

#ifndef UGAME_STATEHEROLIST_H
#define UGAME_STATEHEROLIST_H

#include <core/GameState.h>
#include <SFML/Graphics/Sprite.hpp>
#include <gui/Window.h>

namespace uGame {

    class Application;

    /**
     * State when user pick exists hero or try to create new
     */
    class StateHeroList : public GameState {
    public:
        /**
         * Constructor
         */
        StateHeroList();

        virtual ~StateHeroList();

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
        sf::Texture _bgTexture;
        sf::Sprite _bg;
        Window* _menuFrame;

        /**
         * Center elements of window
         * @param wsize - game window size
         */
        void centerContent(sf::Vector2u wsize);
    };
}

#endif //UGAME_STATEHEROLIST_H
