//
// Created by symbx on 12.08.17.
//

#include <core/AssetsManager.h>
#include <utils/Logger.h>
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
        setSize(_texture.getSize());

        _vertex[0].texCoords = sf::Vector2f(0, 0);
        _vertex[1].texCoords = sf::Vector2f(_size.x, 0);
        _vertex[2].texCoords = sf::Vector2f(0, _size.y);
        _vertex[3].texCoords = sf::Vector2f(_size.x, _size.y);
    }

    Window::~Window() {

    }

    void Window::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= _transform;
        states.texture = &_texture;
        target.draw(_vertex, states);
        target.draw(_title, states);
        for(auto& item : _controls)
            target.draw(*item, states);
    }

    void Window::setPosition(sf::Vector2u pos) {
        _pos = pos;
        _transform = sf::Transform(1, 0, pos.x,
                                   0, 1, pos.y,
                                   0, 0, 1);
        L_INFO("Set pos "+std::to_string(pos.x)+'x'+std::to_string(pos.y));
    }

    void Window::setPosition(sf::Uint32 x, sf::Uint32 y) {
        _pos = sf::Vector2u(x, y);
        _transform = sf::Transform(1, 0, x,
                                   0, 1, y,
                                   0, 0, 1);
        L_INFO("Set pos "+std::to_string(x)+'x'+std::to_string(y));
    }

    void Window::setSize(sf::Vector2u size) {
        _vertex[0].position = sf::Vector2f(0, 0);
        _vertex[1].position = sf::Vector2f(size.x, 0);
        _vertex[2].position = sf::Vector2f(0, size.y);
        _vertex[3].position = sf::Vector2f(size.x, size.y);
        _size = size;

        sf::FloatRect rect = _title.getLocalBounds();
        _title.setPosition((size.x - rect.width)/2, 8);
        L_INFO("Set size "+std::to_string(size.x)+'x'+std::to_string(size.y));
    }

    void Window::setSize(sf::Uint32 w, sf::Uint32 h) {
        _vertex[0].position = sf::Vector2f(0, 0);
        _vertex[1].position = sf::Vector2f(w, 0);
        _vertex[2].position = sf::Vector2f(0, h);
        _vertex[3].position = sf::Vector2f(w, h);
        _size = sf::Vector2u(w, h);

        sf::FloatRect rect = _title.getLocalBounds();
        _title.setPosition((w - rect.width)/2, 8);
        L_INFO("Set size "+std::to_string(w)+'x'+std::to_string(h));
    }

    sf::Vector2u Window::getPosition() {
        return _pos;
    }

    sf::Vector2u Window::getSize() {
        return _size;
    }

}