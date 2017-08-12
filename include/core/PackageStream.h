//
// Created by symbx on 05.08.17.
//

#ifndef UGAME_PACKAGESTREAM_H
#define UGAME_PACKAGESTREAM_H

#include <SFML/System/InputStream.hpp>
#include <string>
#include <fstream>

namespace uGame {

    class PackageStream : public sf::InputStream {
    public:
        PackageStream(const std::string &file, sf::Uint64 offset, sf::Uint64 size);

        sf::Int64 read(void *data, sf::Int64 size);

        sf::Int64 seek(sf::Int64 pos);

        sf::Int64 tell();

        sf::Int64 getSize();

    protected:
        std::ifstream _stream;
        sf::Uint64 _pos;
        sf::Uint64 _size;
        sf::Uint64 _offset;
    };
}

#endif //UGAME_PACKAGESTREAM_H
