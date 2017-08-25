//
// Created by symbx on 25.08.17.
//

#include <gui/UI.h>
#include "gui/Label.h"
namespace uGame {

    Label::Label(const sf::String &text, unsigned int width) :
        _text() {
        _layout = UI::getLayout("/layouts/label.gui");
        setPosition(0 ,0);
        _text.setString(text);
        _text.setFont(*UI::getFont("base"));
        _text.setCharacterSize(static_cast<unsigned int>(_layout->floats[0]));
        _text.setFillColor(_layout->colors[0]);
        _text.setOutlineColor(_layout->colors[1]);
        _text.setOutlineThickness(_layout->floats[1]);
        _width = width;
        _text.setPosition((_width - _text.getLocalBounds().width)/2, 0);
    }

    Label::~Label() {

    }

    void uGame::Label::event(const sf::Event &event) {

    }

    void uGame::Label::update(const float time) {

    }

    void uGame::Label::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(_text, states);
    }

    void Label::setText(const sf::String &text) {
        _text.setString(text);
        _text.setPosition((_width - _text.getLocalBounds().width)/2, 0);
    }

    void Label::setColor(const sf::Color &color) {
        _text.setFillColor(color);
    }
}