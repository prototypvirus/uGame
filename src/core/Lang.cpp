//
// Created by symbx on 22.08.17.
//

#include <core/AssetsManager.h>
#include <cstring>
#include <Constants.h>
#include <utils/Logger.h>
#include <iostream>
#include "core/Lang.h"

namespace uGame {

    std::vector<sf::String> Lang::_dict;

    std::string Lang::current() {
#ifdef _OS_IOS

#elif _OS_ANDROID

#elif _OS_WIN32

#elif _OS_DARWIN

#elif _OS_UNIX
        return std::locale("").name().substr(0, 2);
#else
        return FALLBACK_LANG;
#endif
    }

    void Lang::load() {
        Lang::_dict.clear();
        std::string lng("/langs/" + Lang::current() + ".lng"); //In future change to load from config
        L_INFO("Look for lang "+lng);
        if(!AssetsManager::hasEntry(lng)) {
            lng = "/langs/";
            lng += FALLBACK_LANG;
            lng += ".lng";
        }
        L_INFO("Load lang "+lng);
        sf::InputStream* stream = AssetsManager::getStream(lng);
        sf::Uint32 count;
        sf::Uint32 buffer[1024];
        sf::Uint16 len;
        stream->read(&count, 4);
        for (sf::Uint32 i = 0; i < count; ++i) {
            stream->read(&len, 2);
            if(len > 1024)
                len = 1024;
            memset(buffer, 0, 4096);
            stream->read(buffer, len*4);
            sf::String str(buffer);
            Lang::_dict.push_back(str);
        }
        delete stream;
    }

    sf::String Lang::get(sf::Uint32 id) {
        if(Lang::_dict.size() > id)
            return Lang::_dict[id];
        return L"NULL";
    }
}