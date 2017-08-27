//
// Created by symbx on 22.08.17.
//

#include <SFML/System/String.hpp>
#include <core/AssetsManager.h>
#include <gui/UI.h>
#include "gui/Button.h"
#include "gui/ControlsContainer.h"

namespace uGame {

    Button::Button(const sf::String &text) :
        _texture(),
        _vertex(sf::TrianglesStrip, 4),
        _text() {
        _layout = UI::getLayout("/layouts/menu_button.gui");
        sf::InputStream* stream = AssetsManager::getStream(_layout->images[0]);
        _texture.loadFromStream(*stream);
        delete stream;
        setPosition(0 ,0);
        _text.setString(text);
        _text.setFont(*UI::getFont("base"));
        _text.setCharacterSize(static_cast<unsigned int>(_layout->floats[0]));
        _text.setFillColor(_layout->colors[0]);
        _text.setOutlineColor(_layout->colors[1]);
        _text.setOutlineThickness(_layout->floats[1]);
        //sf::Vector2u tsize = _texture.getSize();

        _size = sf::Vector2f(_layout->points[3].x, _layout->points[3].y);
        _vertex[0].position = sf::Vector2f(0, 0);
        _vertex[1].position = sf::Vector2f(_size.x, 0);
        _vertex[2].position = sf::Vector2f(0, _size.y);
        _vertex[3].position = sf::Vector2f(_size.x, _size.y);

        sf::FloatRect rect = _text.getLocalBounds();
        _text.setPosition(_layout->points[4].x - rect.width/2, _layout->points[4].y - rect.height/2);
        _state = Hover; //Fix for comparing in method
        _press = false;
        setState(Normal);
    }

    Button::~Button() {

    }

    void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = &_texture;
        target.draw(_vertex, states);
        target.draw(_text, states);
    }

    void Button::setState(State state) {
        if(_state == state)
            return;
        _state = state;
        char s = (char)state;
        _vertex[0].texCoords = sf::Vector2f(_layout->points[s].x, _layout->points[s].y);
        _vertex[1].texCoords = sf::Vector2f(_layout->points[s].x + _layout->points[3].x, _layout->points[s].y);
        _vertex[2].texCoords = sf::Vector2f(_layout->points[s].x, _layout->points[s].y + _layout->points[3].y);
        _vertex[3].texCoords = sf::Vector2f(_layout->points[s].x + _layout->points[3].x, _layout->points[s].y + _layout->points[3].y);
        //_press = (state == Press);
    }

    bool Button::isPress() {
        if(!_press)
            return false;
        _press = false;
        return true;
    }

    void Button::event(const sf::Event &event) {
        if(event.type == sf::Event::MouseMoved && _state != Press) {
            sf::FloatRect rect = getGlobalBounds();
            setState(rect.contains(event.mouseMove.x, event.mouseMove.y) ? Hover : Normal);
        }
        if(event.type == sf::Event::TouchMoved && _state != Press && event.touch.finger == 0) {
            sf::FloatRect rect = getGlobalBounds();
            setState(rect.contains(event.mouseMove.x, event.mouseMove.y) ? Hover : Normal);
        }
        if(event.type == sf::Event::MouseButtonPressed) {
            sf::FloatRect rect = getGlobalBounds();
            setState(rect.contains(event.mouseButton.x, event.mouseButton.y) ? Press : Normal);
        }
        if(event.type == sf::Event::TouchBegan && event.touch.finger == 0) {
            sf::FloatRect rect = getGlobalBounds();
            setState(rect.contains(event.touch.x, event.touch.y) ? Press : Normal);
        }
        if(event.type == sf::Event::MouseButtonReleased) {
            sf::FloatRect rect = getGlobalBounds();
            if(rect.contains(event.mouseButton.x, event.mouseButton.y)) {
                _press = (_state == Press);
                setState(Hover);
            }else{
                setState(Normal);
            }
        }
        if(event.type == sf::Event::TouchEnded && event.touch.finger == 0) {
            sf::FloatRect rect = getGlobalBounds();
            if(rect.contains(event.touch.x, event.touch.y)) {
                _press = (_state == Press);
            }
            setState(Normal);
        }
    }

    void Button::update(const float time) {

    }

    sf::FloatRect Button::getLocalBounds() const {
        return sf::FloatRect(0, 0, _size.x, _size.y);
    }

    sf::FloatRect Button::getGlobalBounds() const {
        if(_parent != 0)
            return _parent->getTransform().transformRect(getTransform().transformRect(getLocalBounds()));
        return getTransform().transformRect(getLocalBounds());
    }

    void Button::setText(const sf::String &text) {
        _text.setString(text);
        sf::FloatRect rect = _text.getLocalBounds();
        _text.setPosition(_layout->points[4].x - rect.width/2, _layout->points[4].y - rect.height/2);
    }
}