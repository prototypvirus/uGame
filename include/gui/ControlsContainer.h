//
// Created by symbx on 12.08.17.
//

#ifndef UGAME_CONTROLSCONTAINER_H
#define UGAME_CONTROLSCONTAINER_H

#include <set>
#include <SFML/Graphics/Drawable.hpp>
#include "Control.h"

namespace uGame {
    class ControlsContainer : public sf::Drawable, public sf::Transformable {
    public:
        virtual void addControl(Control* control);
        virtual void removeControl(Control* control);
        virtual void event(const sf::Event& event) = 0;
        virtual void update(const float time) = 0;

    protected:
        std::set<Control*> _controls;
    };
}

#endif //UGAME_CONTROLSCONTAINER_H
