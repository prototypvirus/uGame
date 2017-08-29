//
// Created by symbx on 12.08.17.
//

#ifndef UGAME_CONTROL_H
#define UGAME_CONTROL_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace uGame {

    class ControlsContainer;

    class Control : public sf::Drawable, public sf::Transformable {
    public:
        Control(ControlsContainer* parent = 0);
        virtual void setVisible(bool v);
        virtual bool isVisible();
        virtual bool event(const sf::Event &event) = 0;
        virtual void update(const float time) = 0;
        virtual void focus();

    protected:
        ControlsContainer* _parent;
        bool _visible;
        bool _focus;
        virtual void unfocus();
        friend ControlsContainer;
    };
}

#endif //UGAME_CONTROL_H
