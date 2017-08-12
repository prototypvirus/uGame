//
// Created by symbx on 08.08.17.
//

#ifndef UGAME_STATEMENU_H
#define UGAME_STATEMENU_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <core/GameState.h>
#include <gui/Window.h>

namespace uGame {

    class Application;

    class StateMenu : public GameState {
    public:
        StateMenu();

        ~StateMenu();

        void init(const Application *app) override;

        void event(const sf::Event &event) override;

        void update(const float time) override;

        void draw(sf::RenderWindow &render, const float time) override;

    private:
        Application *_app;
        sf::Texture *_bgTexture;
        sf::RectangleShape *_bg;
        Window* _menuFrame;
        void centerContent(sf::Vector2u wsize);
    };
}

#endif //UGAME_STATEMENU_H
