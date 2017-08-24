//
// Created by symbx on 24.08.17.
//

#include <Constants.h>
#include <core/AssetsManager.h>
#include <utils/Logger.h>
#include <cstring>
#include "gui/UI.h"

namespace uGame {
    std::unordered_map<std::string, sf::Font *> UI::_fonts;

    void uGame::UI::loadFonts() {
        sf::Font *font = new sf::Font();
        font->loadFromFile(FALLBACK_FONT);
        UI::_fonts["fallback"] = font;
        if (!AssetsManager::hasEntry("/cfg/fonts")) {
            L_WARN("No fonts list, only fallback available.");
            return;
        }
        sf::InputStream *stream = AssetsManager::getStream("/cfg/fonts");
        sf::Uint8 count;
        sf::Uint8 len;
        std::string file;
        std::string name;
        char buffer[256];
        stream->read(&count, 1);
        for (sf::Uint8 i = 0; i < count; i++) {
            stream->read(&len, 1);
            memset(buffer, 0, 256);
            stream->read(buffer, len);
            name.assign(buffer, len);
            stream->read(&len, 1);
            memset(buffer, 0, 256);
            stream->read(buffer, len);
            file.assign(buffer, len);
            font = new sf::Font();
            sf::InputStream *fstr = AssetsManager::getStream(file);
            font->loadFromStream(*fstr);
            _fonts[name] = font;
            L_INFO("Load font " + file + " as " + name);
        }
        delete stream;
    }

    sf::Font *UI::getFont(const std::string &font) {
        if(UI::_fonts.count(font) > 0)
            return UI::_fonts[font];
        L_WARN("Font "+font+" not available, use fallback.");
        return UI::_fonts["fallback"];
    }
}
