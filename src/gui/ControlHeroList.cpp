//
// Created by symbx on 01.10.17.
//

#include "gui/ControlHeroList.h"

namespace uGame {

    ControlHeroList::ControlHeroList() {}

    ControlHeroList::~ControlHeroList() {
        _chars.clear();
    }

    bool ControlHeroList::event(const sf::Event &event) {
        return false;
    }

    void ControlHeroList::update(const float time) {

    }

    void ControlHeroList::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    }

    void ControlHeroList::addCharacter(sf::Uint8 type, sf::Uint16 hair, sf::String name) {
        struct CharacterSnap* snap = new CharacterSnap();
        snap->type = type;
        snap->hair = hair;
        snap->name = name;
        _chars.push_back(snap);
    }
}