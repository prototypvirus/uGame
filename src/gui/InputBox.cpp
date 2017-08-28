//
// Created by symbx on 28.08.17.
//

#include <utils/Logger.h>
#include "gui/InputBox.h"
#include "gui/ControlsContainer.h"

namespace uGame {

    InputBox::InputBox(const sf::String &str, int width) :
        _cursorPos(0),
        _maxLength(-1),
        _text(),
        _vertex(sf::TrianglesStrip, 4),
        _tick(0),
        _width(width) {
        _layout = UI::getLayout("/layouts/inputbox.gui");

        _vertex[0].position = sf::Vector2f(0, 0);
        _vertex[1].position = sf::Vector2f(width, 0);
        _vertex[2].position = sf::Vector2f(0, _layout->floats[0]);
        _vertex[3].position = sf::Vector2f(width, _layout->floats[0]);

        _vertex[0].color = _layout->colors[0];
        _vertex[1].color = _layout->colors[0];
        _vertex[2].color = _layout->colors[1];
        _vertex[3].color = _layout->colors[1];

        _text.setFont(*UI::getFont("base"));
        _text.setPosition(_layout->points[0].x, _layout->points[0].y);
        _text.setFillColor(_layout->colors[2]);
        _text.setOutlineColor(_layout->colors[3]);
        _text.setOutlineThickness(_layout->floats[1]);
        _text.setCharacterSize(static_cast<unsigned int>(_layout->floats[2]));
        _text.setString(str);

        _cursor.setFillColor(_layout->colors[4]);
        _cursor.setSize(sf::Vector2f(_layout->floats[3], _layout->floats[0]));
        setCursor(0);
    }

    InputBox::~InputBox() {

    }

    void InputBox::event(const sf::Event &event) {

    }

    void InputBox::update(const float time) {
        _tick += time;
        if(_tick >= _layout->floats[2]) {
            _tick -= _layout->floats[2];
            sf::Color clr = _cursor.getFillColor();
            clr.a = static_cast<sf::Uint8>((clr.a > 0) ? 0 : 255);
            _cursor.setFillColor(clr);
        }
    }

    void InputBox::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = NULL;
        target.draw(_vertex, states);
        target.draw(_text, states);
        target.draw(_cursor, states);
    }

    void InputBox::setText(const sf::String &str) {
        _text.setString(str);
        setCursor(str.getSize());
    }

    const sf::String &InputBox::getText() const {
        return _text.getString();
    }

    void InputBox::setCursor(int pos) {
        if(pos <= _text.getString().getSize()) {
            _cursorPos = pos;
            _cursor.setPosition(_text.findCharacterPos(pos).x, _layout->points[0].y);
            if (_cursor.getPosition().x > getLocalBounds().width - _layout->points[0].x)
            {
                // Shift text on left
                float diff = _cursor.getPosition().x - getLocalBounds().width + _layout->points[0].x;
                _text.move(-diff, 0);
                _cursor.move(-diff, 0);
            }
            else if (_cursor.getPosition().x < _layout->points[0].x)
            {
                // Shift text on right
                float diff = _layout->points[0].x - _cursor.getPosition().x;
                _text.move(diff, 0);
                _cursor.move(diff, 0);
            }

            float text_width = _text.getLocalBounds().width;
            if (_text.getPosition().x < _layout->points[0].x && _text.getPosition().x + text_width < getLocalBounds().width - _layout->points[0].x)
            {
                float diff = (getLocalBounds().width - _layout->points[0].x) - (_text.getPosition().x + text_width);
                _text.move(diff, 0);
                _cursor.move(diff, 0);
                // If text is smaller than the textbox, force align on left
                if (text_width < (getLocalBounds().width - _layout->points[0].x * 2))
                {
                    diff = _layout->points[0].x - _text.getPosition().x;
                    _text.move(diff, 0);
                    _cursor.move(diff, 0);
                }
            }
        }
    }

    int InputBox::getCursor() {
        return _cursorPos;
    }

    sf::FloatRect InputBox::getLocalBounds() const {
        return sf::FloatRect(0, 0, _width, _layout->floats[0]);
    }

    sf::FloatRect InputBox::getGlobalBounds() const {
        if(_parent != 0)
            return _parent->getTransform().transformRect(getTransform().transformRect(getLocalBounds()));
        return getTransform().transformRect(getLocalBounds());
    }
}