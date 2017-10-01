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
    /**
     * Translater class
     */
    class Lang {
    public:
        /**
         * Load language from file
         */
        static void load();

        /**
         * Get translation by id
         * @param id - translation id
         * @return translated string
         */
        static sf::String get(sf::Uint32 id);

    protected:
        /**
         * Get current system language
         * @return system language code (2 chars)
         */
        static std::string current();
        static std::vector<sf::String> _dict;
    };
}


#endif //UGAME_LANG_H
