//
// Created by symbx on 22.08.17.
//

#include <SFML/System/String.hpp>
#include <core/AssetsManager.h>
#include "gui/Button.h"

namespace uGame {

    Button::Button(const sf::String &text) :
        _texture(),
        _vertex(sf::TrianglesStrip, 4),
        _text() {
        sf::InputStream* stream = AssetsManager::getStream("/imgs/ui/menu_button.png");
        _texture.loadFromStream(*stream);
        delete stream;
        setPosition(0 ,0);
        _text.setString(text);
        _text.setFont(*AssetsManager::getFont("base"));
        _text.setCharacterSize(18);
        _text.setFillColor(sf::Color::White);
        _text.setOutlineColor(sf::Color::Black);
        _text.setOutlineThickness(1.0f);
        sf::Vector2u tsize = _texture.getSize();
        _size = sf::Vector2f(tsize.x, tsize.y/3.0f);
        _vertex[0].position = sf::Vector2f(0, 0);
        _vertex[1].position = sf::Vector2f(_size.x, 0);
        _vertex[2].position = sf::Vector2f(0, _size.y);
        _vertex[3].position = sf::Vector2f(_size.x, _size.y);
        sf::FloatRect rect = _text.getLocalBounds();
        _text.setPosition((_size.x - rect.width)/2, (_size.y - rect.height)/2);
        setState(0);
    }

    Button::~Button() {

    }

    void Button::setVisible(bool v) {
        _visible = v;
    }

    bool Button::isVisible() {
        return _visible;
    }

    void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = &_texture;
        target.draw(_vertex, states);
        target.draw(_text, states);
    }

    void Button::setState(char state) {
        _vertex[0].texCoords = sf::Vector2f(0, state*_size.y);
        _vertex[1].texCoords = sf::Vector2f(_size.x, state*_size.y);
        state++;
        _vertex[2].texCoords = sf::Vector2f(0, state*_size.y);
        _vertex[3].texCoords = sf::Vector2f(_size.x, state*_size.y);
    }

    bool Button::isPress() {
        return false;
    }

    void Button::event(const sf::Event &event) {
        if(event.type == sf::Event::MouseMoved) {

        }
    }

    void Button::update(const float time) {

    }

    sf::FloatRect Button::getLocalBounds() const {
        return sf::FloatRect(0, 0, _size.x, _size.y);
    }

    sf::FloatRect Button::getGlobalBounds() const {
        return getTransform().transformRect(getLocalBounds());
    }
}