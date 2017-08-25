//
// Created by symbx on 24.08.17.
//

#ifndef UGAME_UI_H
#define UGAME_UI_H

#include <SFML/Graphics/Font.hpp>
#include <unordered_map>
#include <string>

namespace uGame {
    struct Layout {
        std::string* images;
        sf::IntRect* rects;
        sf::Vector2u* points;
        sf::Color* colors;
        float* floats;
    };

    class UI {
    public:
        static void loadFonts();

        static sf::Font* getFont(const std::string& font);

        static struct Layout* getLayout(const std::string& f);

        static void clean();

    protected:
        static std::unordered_map<std::string, sf::Font*> _fonts;
        static std::unordered_map<std::string, struct Layout*> _layouts;

        static struct Layout* loadLayout(const std::string& f);
    };
}

#endif //UGAME_UI_H
