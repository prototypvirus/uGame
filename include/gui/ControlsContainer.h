//
// Created by symbx on 12.08.17.
//

#ifndef UGAME_CONTROLSCONTAINER_H
#define UGAME_CONTROLSCONTAINER_H

#include <set>
#include <SFML/Graphics/Drawable.hpp>
#include "Control.h"

namespace uGame {
    class ControlsContainer : public sf::Drawable {
    public:
        virtual void addControl(Control* control);
        virtual void removeControl(Control* control);

    protected:
        std::set<Control*> _controls;
    };
}

#endif //UGAME_CONTROLSCONTAINER_H
