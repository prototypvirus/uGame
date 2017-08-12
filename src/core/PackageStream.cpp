//
// Created by symbx on 05.08.17.
//

#include "core/PackageStream.h"

namespace uGame {

    PackageStream::PackageStream(const std::string &file, sf::Uint64 offset, sf::Uint64 size) :
            _stream(file) {
        _pos = 0;
        _offset = offset;
        _size = size;
        _stream.seekg(offset, _stream.beg);
    }

    sf::Int64 PackageStream::read(void *data, sf::Int64 size) {
        sf::Int64 len = size;
        if (_pos + size >= _size)
            len = _size - _pos;
        _stream.read((char *) data, len);
        len = _stream.gcount();
        _pos += len;
        return len;
    }

    sf::Int64 PackageStream::seek(sf::Int64 pos) {
        _stream.seekg(_offset + pos, _stream.beg);
        _pos = pos;
        return pos;
    }

    sf::Int64 PackageStream::tell() {
        return _pos;
    }

    sf::Int64 PackageStream::getSize() {
        return _size;
    }

}