//
// Created by symbx on 12.08.17.
//

#include "gui/ControlsContainer.h"

namespace uGame {

    void ControlsContainer::addControl(Control *control) {
        if(control->_parent != 0)
            control->_parent->removeControl(control);
        control->_parent = this;
        _controls.insert(control);
    }

    void ControlsContainer::removeControl(Control *control) {
        _controls.erase(control);
        control->_parent = 0;
    }

    void ControlsContainer::focusMe(Control *control) {
        for(auto& i : _controls) {
            if(i != control)
                i->unfocus();
        }
    }
}