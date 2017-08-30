//
// Created by symbx on 12.08.17.
//

#include <core/AssetsManager.h>
#include <gui/UI.h>
#include <utils/Logger.h>
#include "gui/Window.h"

namespace uGame {
    Window::Window(const sf::String &title) :
        _texture(),
        _vertex(sf::TrianglesStrip, 4),
        _title() {
        _layout = UI::getLayout("/layouts/window.gui");
        sf::InputStream* stream = AssetsManager::getStream(_layout->images[0]);
        _texture.loadFromStream(*stream);
        delete stream;

        setPosition(0, 0);
        _title.setString(title);
        _title.setFont(*UI::getFont("base"));
        _title.setCharacterSize(static_cast<unsigned int>(_layout->floats[0]));
        _title.setFillColor(_layout->colors[0]);
        _title.setOutlineColor(_layout->colors[1]);
        _title.setOutlineThickness(_layout->floats[1]);
        _size = sf::Vector2f(_layout->points[0].x, _layout->points[0].y);

        sf::IntRect rect = _layout->rects[0];

        _vertex[0].texCoords = sf::Vector2f(rect.left, rect.top);
        _vertex[1].texCoords = sf::Vector2f(rect.left+rect.width, rect.top);
        _vertex[2].texCoords = sf::Vector2f(rect.left, rect.top+rect.height);
        _vertex[3].texCoords = sf::Vector2f(rect.left+rect.width, rect.top+rect.height);

        _vertex[0].position = sf::Vector2f(0, 0);
        _vertex[1].position = sf::Vector2f(_size.x, 0);
        _vertex[2].position = sf::Vector2f(0, _size.y);
        _vertex[3].position = sf::Vector2f(_size.x, _size.y);

        sf::FloatRect trect = _title.getLocalBounds();
        _title.setPosition(_layout->points[1].x - (trect.width/2), _layout->points[1].y);
        _close = false;
        _press = false;
    }

    Window::~Window() {

    }

    void Window::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = &_texture;
        target.draw(_vertex, states);
        target.draw(_title, states);
        for(auto& item : _controls)
            target.draw(*item, states);
    }

    sf::FloatRect Window::getLocalBounds() const {
        return sf::FloatRect(0, 0, _size.x, _size.y);
    }

    sf::FloatRect Window::getGlobalBounds() const {
        return getTransform().transformRect(getLocalBounds());
    }

    bool Window::event(const sf::Event &event) {
        for(auto& item : _controls)
            if(item->event(event)) {
                return true;
            }
        if(event.type == sf::Event::MouseButtonPressed) {
            sf::IntRect rect = _layout->rects[1];
            _press = getTransform().transformRect(sf::FloatRect(rect.left, rect.top, rect.width, rect.height)).contains(event.mouseButton.x, event.mouseButton.y);
            return true;
        }
        if(event.type == sf::Event::TouchBegan && event.touch.finger == 0) {
            sf::IntRect rect = _layout->rects[1];
            _press = getTransform().transformRect(sf::FloatRect(rect.left, rect.top, rect.width, rect.height)).contains(event.touch.x, event.touch.y);
        }
        if(event.type == sf::Event::MouseButtonReleased) {
            sf::IntRect rect = _layout->rects[1];
            _close = (_press && getTransform().transformRect(sf::FloatRect(rect.left, rect.top, rect.width, rect.height)).contains(event.mouseButton.x, event.mouseButton.y));
            _press = false;
            return true;
        }
        if(event.type == sf::Event::TouchEnded && event.touch.finger == 0) {
            sf::IntRect rect = _layout->rects[1];
            _close = (_press && getTransform().transformRect(sf::FloatRect(rect.left, rect.top, rect.width, rect.height)).contains(event.touch.x, event.touch.y));
            _press = false;
        }
        return false;
    }

    void Window::update(const float time) {
        for(auto& item : _controls)
            item->update(time);
    }

    bool Window::isClose() {
        if(!_close)
            return false;
        _close = false;
        return true;
    }
}