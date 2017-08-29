//
// Created by symbx on 12.08.17.
//

#include "gui/Control.h"
#include "gui/ControlsContainer.h"

namespace uGame {

    Control::Control(ControlsContainer *parent) {
        _parent = parent;
    }

    void Control::setVisible(bool v) {
        _visible = v;
    }

    bool Control::isVisible() {
        return _visible;
    }

    void Control::focus() {
        _focus = true;
        if(_parent != NULL)
            _parent->focusMe(this);
    }

    void Control::unfocus() {
        _focus = false;
    }
}