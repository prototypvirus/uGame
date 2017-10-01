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

    /**
     * Gui control
     */
    class Control : public sf::Drawable, public sf::Transformable {
    public:
        /**
         * Constructor
         * @param parent - parent container
         */
        Control(ControlsContainer* parent = 0);

        /**
         * Set visibility of control
         * @param v - visible?
         */
        virtual void setVisible(bool v);

        /**
         * Get visibility of cintrol
         * @return visible?
         */
        virtual bool isVisible();

        /**
         * Handle events
         * @param event - event object
         * @return event handled (if true do not send next control)
         */
        virtual bool event(const sf::Event &event) = 0;

        /**
         * Handle updates
         * @param time - time elapsed from last update
         */
        virtual void update(const float time) = 0;

        /**
         * Focus current control
         */
        virtual void focus();

    protected:
        ControlsContainer* _parent;
        bool _visible;
        bool _focus;

        /**
         * Blur current control
         */
        virtual void unfocus();
        friend ControlsContainer;
    };
}

#endif //UGAME_CONTROL_H
