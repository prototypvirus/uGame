//
// Created by symbx on 29.08.17.
//

#ifndef UGAME_STATEPLAY_H
#define UGAME_STATEPLAY_H

#include <core/GameState.h>
#include <SFML/Graphics/RenderWindow.hpp>

namespace uGame {
    class StatePlay : public GameState {
    public:
        StatePlay();

        virtual ~StatePlay();

        void init(const Application *app) override;

        void event(const sf::Event &event) override;

        void update(const float time) override;

        void draw(sf::RenderWindow &render) override;

    protected:
        Application* _app;
    };
}

#endif //UGAME_STATEPLAY_H
