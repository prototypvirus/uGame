//
// Created by symbx on 28.08.17.
//

#include <utils/Logger.h>
#include "gui/InputBox.h"
#include "gui/ControlsContainer.h"
#include <SFML/OpenGL.hpp>

namespace uGame {

    InputBox::InputBox(int width) :
        _cursorPos(0),
        _maxLength(-1),
        _text(),
        _vertex(sf::TrianglesStrip, 4),
        _tick(0),
        _width(width),
        _return(false),
        _range(0) {
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

        _cursor.setFillColor(_layout->colors[4]);
        _cursor.setSize(sf::Vector2f(_layout->floats[3], _layout->floats[0]));
        setCursor(0);
    }

    InputBox::~InputBox() {

    }

    bool InputBox::event(const sf::Event &event) {
        if(event.type == sf::Event::MouseButtonPressed) {
            sf::FloatRect rect = getGlobalBounds();
            if(rect.contains(event.mouseButton.x, event.mouseButton.y)) {
                focus();
                int x = event.mouseButton.x - rect.left;
                for (int i = _text.getString().getSize(); i >= 0; --i)
                {
                    // Place cursor after the character under the mouse
                    sf::Vector2f glyph_pos = _text.findCharacterPos(i);
                    if (glyph_pos.x <= x)
                    {
                        setCursor(i);
                        break;
                    }
                }
#ifdef _OS_ANDROID
                sf::Keyboard::setVirtualKeyboardVisible(true);
                //Utils::showKeyboard(true);
#endif
                return true;
            }
        }
        if(event.type == sf::Event::TouchBegan && event.touch.finger == 0) {
            sf::FloatRect rect = getGlobalBounds();
            if(rect.contains(event.touch.x, event.touch.y)) {
                focus();
                int x = event.touch.x - rect.left;
                for (int i = _text.getString().getSize(); i >= 0; --i)
                {
                    // Place cursor after the character under the mouse
                    sf::Vector2f glyph_pos = _text.findCharacterPos(i);
                    if (glyph_pos.x <= x)
                    {
                        setCursor(i);
                        break;
                    }
                }
#ifdef _OS_ANDROID
                sf::Keyboard::setVirtualKeyboardVisible(true);
                //Utils::showKeyboard(true);
#endif
            }
        }
        if(!_focus)
            return false;
        if(event.type == sf::Event::KeyPressed) {
            //L_INFO("KeyPress "+std::to_string(event.key.code)+'/'+std::to_string(sf::Keyboard::KeyCount));
            switch ((int)event.key.code) {
                case sf::Keyboard::Left:
                    setCursor(_cursorPos - 1);
                    return true;

                case sf::Keyboard::Right:
                    setCursor(_cursorPos + 1);
                    return true;

                case sf::Keyboard::BackSpace: //Android incorrect (backspace = normal delete(66) | delete = 112)
                    // Erase character before cursor
                    if (_cursorPos > 0) {
                        sf::String string = _text.getString();
                        string.erase(_cursorPos - 1);
                        _text.setString(string);

                        setCursor(_cursorPos - 1);
                    }
                    return true;

                case sf::Keyboard::Delete:
                    // Erase character after cursor
                    if (_cursorPos < _text.getString().getSize()) {
                        sf::String string = _text.getString();
                        string.erase(_cursorPos);
                        _text.setString(string);

                        setCursor(_cursorPos);
                    }
                    return true;

                case sf::Keyboard::Home:
                    setCursor(0);
                    return true;

                case sf::Keyboard::End:
                    setCursor(_text.getString().getSize());
                    return true;

                case sf::Keyboard::Return:
                    _return = true;
                    return true;

                default:
                    break;
            }
            return false;
        }

        if(event.type == sf::Event::TextEntered) {
            //L_INFO("TextEnter "+std::to_string(event.text.unicode));
            if (event.text.unicode > 30 && checkRange(event.text.unicode))
            {
                sf::String string = _text.getString();
                if (_maxLength == -1 || (int) string.getSize() < _maxLength)
                {
                    // Insert character in string at cursor position
                    string.insert(_cursorPos, event.text.unicode);
                    _text.setString(string);

                    setCursor(_cursorPos + 1);
                }
            }
            return true;
        }
        return false;
    }

    void InputBox::update(const float time) {
        _tick += time;
        if(_tick >= _layout->floats[4]) {
            _tick -= _layout->floats[4];
            sf::Color clr = _cursor.getFillColor();
            clr.a = static_cast<sf::Uint8>((clr.a > 0) ? 0 : 255);
            _cursor.setFillColor(clr);
        }
    }

    void InputBox::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();
        //const sf::Texture* t = states.texture; //fire bug (parent texture losing)
        states.texture = NULL;
        target.draw(_vertex, states);
        glEnable(GL_SCISSOR_TEST);
        sf::FloatRect rect = getGlobalBounds();
        glScissor(rect.left + _layout->points[0].x, rect.top + _layout->points[0].y, rect.left + rect.width - _layout->points[0].x, rect.top +  rect.height - _layout->points[0].y);
        target.draw(_text, states);
        glDisable(GL_SCISSOR_TEST);
        //states.texture = t;
        if(_focus)
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
        return {0, 0, _width, _layout->floats[0]};
    }

    sf::FloatRect InputBox::getGlobalBounds() const {
        if(_parent != 0)
            return _parent->getTransform().transformRect(getTransform().transformRect(getLocalBounds()));
        return getTransform().transformRect(getLocalBounds());
    }

    void InputBox::setCharacterRange(InputBox::Range r) {
        _range = r;
    }

    bool InputBox::checkRange(sf::Uint32 chr) {
        switch (_range) {
            case Numeric:
                return (chr > 47 && chr < 58);
            case Latin:
                return (chr > 47 && chr < 58) || (chr > 96 && chr < 123);
            case LatinNoNumeric:
                return (chr > 96 && chr < 123);
            case Normal:
            default:
                return (chr < 127 || chr > 159);
        }
    }

    bool InputBox::isReturn() {
        if(!_return)
            return false;
        _return = false;
        return true;
    }
}