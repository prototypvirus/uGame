//
// Created by symbx on 12.08.17.
//

#ifndef UGAME_CONTROL_H
#define UGAME_CONTROL_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>

namespace uGame {

    class Control : public sf::Drawable {
    public:
        Control(Control* parent = 0);
        virtual void setPosition(sf::Vector2f pos) = 0;
        virtual sf::Vector2f getPosition() = 0;
        virtual void setSize(sf::Vector2f size) = 0;
        virtual sf::Vector2f getSize() = 0;
        virtual void setVisible(bool v) = 0;
        virtual bool isVisible() = 0;

    protected:
        Control* _parent;
    };
}

#endif //UGAME_CONTROL_H
