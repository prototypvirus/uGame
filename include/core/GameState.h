//
// Created by symbx on 08.08.17.
//

#ifndef UGAME_GAMESTATE_H
#define UGAME_GAMESTATE_H

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace uGame {

    class Application;

    class GameState {
    public:
        virtual void init(const Application *app) = 0;

        virtual void event(const sf::Event &event) = 0;

        virtual void update(const float time) = 0;

        virtual void draw(sf::RenderWindow &render) = 0;

    };
}

#endif //UGAME_GAMESTATE_H
