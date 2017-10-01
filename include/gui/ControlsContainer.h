//
// Created by symbx on 12.08.17.
//

#ifndef UGAME_CONTROLSCONTAINER_H
#define UGAME_CONTROLSCONTAINER_H

#include <set>
#include <SFML/Graphics/Drawable.hpp>
#include "Control.h"

namespace uGame {

    /**
     * Controls container
     */
    class ControlsContainer : public sf::Drawable, public sf::Transformable {
    public:
        /**
         * Add control to container
         * @param control - control to add
         */
        virtual void addControl(Control* control);

        /**
         * Remove control from container
         * @param control - control to remove
         */
        virtual void removeControl(Control* control);

        /**
         * Handle events
         * @param event - event object
         * @return handled (if true do not send to next control)
         */
        virtual bool event(const sf::Event &event) = 0;

        /**
         * Handle updates
         * @param time - time elapsed from last update
         */
        virtual void update(const float time) = 0;

    protected:
        std::set<Control*> _controls;

        /**
         * Focus given control
         * @param control - control to focus
         */
        virtual void focusMe(Control* control);
        friend Control;
    };
}

#endif //UGAME_CONTROLSCONTAINER_H
