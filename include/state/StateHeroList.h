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

    class StateHeroList : public GameState {
    public:
        StateHeroList();

        virtual ~StateHeroList();

        void init(const Application *app) override;

        void event(const sf::Event &event) override;

        void update(const float time) override;

        void draw(sf::RenderWindow &render) override;

    protected:
        Application* _app;
        sf::Texture _bgTexture;
        sf::Sprite _bg;
        Window* _menuFrame;
        void centerContent(sf::Vector2u wsize);
    };
}

#endif //UGAME_STATEHEROLIST_H
