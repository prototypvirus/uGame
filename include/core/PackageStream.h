//
// Created by symbx on 05.08.17.
//

#ifndef UGAME_PACKAGESTREAM_H
#define UGAME_PACKAGESTREAM_H

#include <SFML/System/InputStream.hpp>
#include <string>
#include <fstream>

namespace uGame {

    /**
     * Stream to file in package
     */
    class PackageStream : public sf::InputStream {
    public:
        /**
         * Constructor
         * @param file - path to resource package
         * @param offset - offset in package
         * @param size - size of file
         */
        PackageStream(const std::string &file, sf::Uint64 offset, sf::Uint64 size);

        /**
         * Read data from package
         * @param data - target buffer
         * @param size - size to read
         * @return count readed bytes
         */
        sf::Int64 read(void *data, sf::Int64 size);

        /**
         * Seek position to...
         * @param pos - new position
         * @return new position
         */
        sf::Int64 seek(sf::Int64 pos);

        /**
         * Get current position
         * @return current position
         */
        sf::Int64 tell();

        /**
         * Get size of file
         * @return size of file
         */
        sf::Int64 getSize();

    protected:
        std::ifstream _stream;
        sf::Uint64 _pos;
        sf::Uint64 _size;
        sf::Uint64 _offset;
    };
}

#endif //UGAME_PACKAGESTREAM_H
