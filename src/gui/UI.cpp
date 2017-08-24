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
    std::unordered_map<std::string, struct Layout *> UI::_layouts;

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

    Layout *UI::getLayout(const std::string &f) {
        if(UI::_layouts.count(f) > 0)
            return UI::_layouts[f];
        return UI::loadLayout(f);
    }

    void UI::clean() {
        for(auto& it : UI::_layouts) {
            delete[] it.second->images;
            delete[] it.second->rects;
            delete[] it.second->points;
        }
        UI::_layouts.clear();
    }

    Layout *UI::loadLayout(const std::string &f) {
        sf::InputStream* stream = AssetsManager::getStream(f);
        if(stream == NULL)
            return NULL;
        Layout* lay = new Layout();
        sf::Uint32 count;
        char buffer[256];
        stream->read(&count, 4);
        lay->images = new std::string[count];
        for (int i = 0; i < count; ++i) {
            char len;
            std::string img;
            memset(buffer, 0, 256);
            stream->read(&len, 1);
            stream->read(buffer, len);
            img.assign(buffer, len);
            lay->images[i] = img;
        }
        stream->read(&count, 4);
        lay->rects = new sf::IntRect[count];
        for (int i = 0; i < count; ++i) {
            sf::IntRect rect;
            stream->read(&rect.left, 4);
            stream->read(&rect.top, 4);
            stream->read(&rect.width, 4);
            stream->read(&rect.height, 4);
        }
        stream->read(&count, 4);
        lay->points = new sf::Vector2u[count];
        for (int i = 0; i < count; ++i) {
            sf::Vector2u dot;
            stream->read(&dot.x, 4);
            stream->read(&dot.y, 4);
        }
        UI::_layouts[f] = lay;
        delete stream;
        return lay;
    }
}
