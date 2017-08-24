//
// Created by symbx on 24.08.17.
//

#ifndef UGAME_UI_H
#define UGAME_UI_H

#include <SFML/Graphics/Font.hpp>
#include <unordered_map>
#include <string>

namespace uGame {
    class UI {
    public:
        static void loadFonts();

        static sf::Font* getFont(const std::string& font);
    protected:
        static std::unordered_map<std::string, sf::Font*> _fonts;
    };
}

#endif //UGAME_UI_H
