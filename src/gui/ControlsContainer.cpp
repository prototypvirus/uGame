//
// Created by symbx on 12.08.17.
//

#include "gui/ControlsContainer.h"

namespace uGame {

    void ControlsContainer::addControl(Control *control) {
        _controls.insert(control);
    }

    void ControlsContainer::removeControl(Control *control) {
        _controls.erase(control);
    }
}