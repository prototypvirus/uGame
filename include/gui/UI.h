//
// Created by symbx on 24.08.17.
//

#ifndef UGAME_UI_H
#define UGAME_UI_H

#include <SFML/Graphics/Font.hpp>
#include <unordered_map>
#include <string>

namespace uGame {
    /**
     * Layout data entry
     */
    struct Layout {
        std::string* images;
        sf::IntRect* rects;
        sf::Vector2u* points;
        sf::Color* colors;
        float* floats;
    };

    /**
     * Storage/loader of layouts (static class)
     */
    class UI {
    public:
        /**
         * Load fonts from package file & fallback font
         */
        static void loadFonts();

        /**
         * Get one of loaded fonts
         * @param font - font name
         * @return pointer of font (DON'T DELETE IT)
         */
        static sf::Font* getFont(const std::string& font);

        /**
         * Get one of loaded layout
         * @param f - path of file with layout
         * @return pointer of layout struct (DON'T DELETE IT)
         */
        static struct Layout* getLayout(const std::string& f);

        /**
         * Cleanup all loaded pointers
         */
        static void clean();

    protected:
        static std::unordered_map<std::string, sf::Font*> _fonts;
        static std::unordered_map<std::string, struct Layout*> _layouts;

        /**
         * Load layout from file
         * @param f - path to file with layout
         * @return pointer of layout
         */
        static struct Layout* loadLayout(const std::string& f);
    };
}

#endif //UGAME_UI_H
