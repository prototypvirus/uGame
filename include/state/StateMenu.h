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

    class StateMenu : public GameState {
    public:
        StateMenu();

        ~StateMenu();

        void init(const Application *app) override;

        void event(const sf::Event &event) override;

        void update(const float time) override;

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
        void centerContent(sf::Vector2u wsize);
    };
}

#endif //UGAME_STATEMENU_H
