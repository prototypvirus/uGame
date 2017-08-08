//
// Created by symbx on 08.08.17.
//

#ifndef UGAME_STATELOADING_H
#define UGAME_STATELOADING_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Thread.hpp>
#include <core/GameState.h>
#include "core/Application.h"

class StateLoading : public GameState {
public:
    StateLoading();
    ~StateLoading();
    void init(const Application *app) override;
    void update(const float time) override;
    void event(const sf::Event &event) override;
    void draw(sf::RenderWindow &render, const float time) override;

private:
    sf::Sprite* _logo;
    sf::Text* _loadText;
    sf::Texture* _logoTexture;
    sf::RectangleShape* _progressBack;
    sf::RectangleShape* _progress;
    sf::Font* _font;
    void centerContent(sf::Vector2u wsize);
    void centerText(sf::Vector2u wsize);
    bool _progressVisible;
    void setProgress(float val);
    void setText(const std::string& msg);
    sf::Thread* _work;
    Application* _app;
};


#endif //UGAME_STATELOADING_H
