//
// Created by symbx on 27.08.17.
//

#ifndef UGAME_STATESIGNIN_H
#define UGAME_STATESIGNIN_H

#include <core/GameState.h>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <gui/Window.h>
#include <gui/Label.h>
#include <gui/Button.h>
#include <gui/InputBox.h>

namespace uGame {

    class Application;

    class StateSignIn : public GameState {
    public:
        StateSignIn();

        virtual ~StateSignIn();

        void init(const Application *app) override;

        void event(const sf::Event &event) override;

        void update(const float time) override;

        void draw(sf::RenderWindow &render) override;

    protected:
        Application* _app;
        sf::Texture _bgTexture;
        sf::Sprite _bg;
        Window* _menuFrame;
        Label* _labelUser;
        Label* _labelPass;
        Button* _enterBtn;
        Button* _backBtn;
        InputBox* _userInput;
        InputBox* _passInput;
        void centerContent(sf::Vector2u wsize);
    };
}

#endif //UGAME_STATESIGNIN_H
