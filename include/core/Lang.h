//
// Created by symbx on 22.08.17.
//

#ifndef UGAME_LANG_H
#define UGAME_LANG_H

#include <SFML/Config.hpp>
#include <SFML/System/String.hpp>
#include <string>
#include <locale>
#include <vector>

namespace uGame {
    class Lang {
    public:
        static void load();
        static sf::String get(sf::Uint32 id);

    protected:
        static std::string current();
        static std::vector<sf::String> _dict;
    };
}


#endif //UGAME_LANG_H
