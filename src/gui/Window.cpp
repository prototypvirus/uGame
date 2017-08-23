//
// Created by symbx on 12.08.17.
//

#include <core/AssetsManager.h>
#include "gui/Window.h"

namespace uGame {
    Window::Window(const sf::String &title) :
        _texture(),
        _vertex(sf::TrianglesStrip, 4),
        _title() {
        sf::InputStream* stream = AssetsManager::getStream("/imgs/ui/frame.png");
        _texture.loadFromStream(*stream);
        delete stream;
        setPosition(0, 0);
        _title.setString(title);
        _title.setFont(*AssetsManager::getFont("base"));
        _title.setCharacterSize(18);
        _title.setFillColor(sf::Color::White);
        _title.setOutlineColor(sf::Color::Black);
        _title.setOutlineThickness(1.0f);
        sf::Vector2u size = _texture.getSize();
        _size = sf::Vector2f(size.x, size.y);

        _vertex[0].texCoords = sf::Vector2f(0, 0);
        _vertex[1].texCoords = sf::Vector2f(size.x, 0);
        _vertex[2].texCoords = sf::Vector2f(0, size.y);
        _vertex[3].texCoords = sf::Vector2f(size.x, size.y);

        _vertex[0].position = sf::Vector2f(0, 0);
        _vertex[1].position = sf::Vector2f(size.x, 0);
        _vertex[2].position = sf::Vector2f(0, size.y);
        _vertex[3].position = sf::Vector2f(size.x, size.y);

        sf::FloatRect rect = _title.getLocalBounds();
        _title.setPosition((size.x - rect.width)/2, 8);
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

    void Window::event(const sf::Event &event) {
        for(auto& item : _controls)
            item->event(event);
    }

    void Window::update(const float time) {
        for(auto& item : _controls)
            item->update(time);
    }
}