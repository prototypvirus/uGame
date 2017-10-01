//
// Created by symbx on 01.10.17.
//

#ifndef UGAME_CONTROLHEROLIST_H
#define UGAME_CONTROLHEROLIST_H

#include <gui/Control.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <vector>

namespace uGame {

    /**
     * Control: horizontal list of characters (icons)
     */
    class ControlHeroList : public Control {
    public:
        struct CharacterSnap {
            sf::Uint8 type;
            sf::Uint16 hair;
            sf::String name;
        };
        ControlHeroList();

        virtual ~ControlHeroList();

        bool event(const sf::Event &event) override;

        void update(const float time) override;

        /**
         * @param type - {4 bits ~ faction + 4 bits ~ class}
         * @param hair - {8 bits ~ haircut + 8 bits ~ color}
         * @param name - {name of character}
         */
        void addCharacter(sf::Uint8 type, sf::Uint16 hair, sf::String name);

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        std::vector<struct CharacterSnap*> _chars;
    };
}

#endif //UGAME_CONTROLHEROLIST_H
