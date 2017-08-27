//
// Created by symbx on 27.08.17.
//

#include <fstream>
#include <cstring>
#include <utils/Logger.h>
#include "core/Config.h"

namespace uGame {

    Config::Config(const std::string &filename) {
        _path = filename;
        load();
    }

    Config::~Config() {

    }

    void Config::load() {
        std::ifstream stream(_path);
        if(!stream.is_open()) {
            L_WARN("Configuration not exists, fill defaults.");
            defaults();
            save();
            return;
        }
        L_INFO("Load configuration.");
        std::string param;
        std::string val;
        char buffer[256];
        sf::Uint8 len;
        sf::Uint32 count;
        stream.read((char*)&count, 4);
        for (int i = 0; i < count; ++i) {
            stream.read((char*)&len, 1);
            memset(buffer, 0, 256);
            stream.read(buffer, len);
            param.assign(buffer, len);

            stream.read((char*)&len, 1);
            memset(buffer, 0, 256);
            stream.read(buffer, len);
            val.assign(buffer, len);

            _map[param] = val;
            L_INFO(param+'='+val);
        }

        stream.close();
    }

    void Config::save() {
        std::ofstream stream(_path);
        if(!stream.is_open()) {
            L_ERR("Can't save configuration!");
            return;
        }
        L_INFO("Save configuration.");
        sf::Uint32 count = _map.size();
        stream.write((char*)&count, 4);
        for(auto& it : _map) {
            sf::Uint8 len = it.first.length();
            stream.write((char*)&len, 1);
            stream.write(it.first.c_str(), len);
            len = it.second.length();
            stream.write((char*)&len, 1);
            stream.write(it.second.c_str(), len);
            L_INFO(it.first+'='+it.second);
        }

        stream.flush();
        stream.close();
    }

    void Config::defaults() {
        _map["volumeMusic"] = "16";
        _map["volumeEffect"] = "32";
    }

    std::string Config::get(const std::string &key, const std::string &def) {
        if(_map.count(key) < 1) {
            _map[key] = def;
            save();
        }
        return _map[key];
    }

    sf::Int8 Config::get(const std::string &key, const sf::Int8 def) {
        if(_map.count(key) < 1) {
            _map[key] = std::to_string(+def);
            save();
        }
        return (sf::Int8)std::stol(_map[key]);
    }

    sf::Uint8 Config::get(const std::string &key, const sf::Uint8 def) {
        if(_map.count(key) < 1) {
            _map[key] = std::to_string(+def);
            save();
        }
        return (sf::Uint8)std::stol(_map[key]);
    }

    sf::Int16 Config::get(const std::string &key, const sf::Int16 def) {
        if(_map.count(key) < 1) {
            _map[key] = std::to_string(def);
            save();
        }
        return (sf::Int16)std::stol(_map[key]);
    }

    sf::Uint16 Config::get(const std::string &key, const sf::Uint16 def) {
        if(_map.count(key) < 1) {
            _map[key] = std::to_string(def);
            save();
        }
        return (sf::Uint16)std::stol(_map[key]);
    }

    sf::Int32 Config::get(const std::string &key, const sf::Int32 def) {
        if(_map.count(key) < 1) {
            _map[key] = std::to_string(def);
            save();
        }
        return (sf::Int32)std::stol(_map[key]);
    }

    sf::Uint32 Config::get(const std::string &key, const sf::Uint32 def) {
        if(_map.count(key) < 1) {
            _map[key] = std::to_string(def);
            save();
        }
        return (sf::Uint32)std::stol(_map[key]);
    }

    sf::Int64 Config::get(const std::string &key, const sf::Int64 def) {
        if(_map.count(key) < 1) {
            _map[key] = std::to_string(def);
            save();
        }
        return (sf::Int64)std::stol(_map[key]);
    }

    sf::Uint64 Config::get(const std::string &key, const sf::Uint64 def) {
        if(_map.count(key) < 1) {
            _map[key] = std::to_string(def);
            save();
        }
        return (sf::Uint64)std::stol(_map[key]);
    }

    float Config::get(const std::string &key, const float def) {
        if(_map.count(key) < 1) {
            _map[key] = std::to_string(def);
            save();
        }
        return (float)std::stol(_map[key]);
    }

    double Config::get(const std::string &key, double def) {
        if(_map.count(key) < 1) {
            _map[key] = std::to_string(def);
            save();
        }
        return (double)std::stol(_map[key]);
    }
}