//
// Created by symbx on 27.08.17.
//

#ifndef UGAME_CONFIG_H
#define UGAME_CONFIG_H

#include <string>
#include <SFML/Config.hpp>
#include <unordered_map>

namespace uGame {
    class Config {
    public:
        Config(const std::string &filename);

        virtual ~Config();

        void load();

        void save();

        std::string get(const std::string& key, const std::string& def);

        sf::Int8 get(const std::string& key, const sf::Int8 def);

        sf::Uint8 get(const std::string& key, const sf::Uint8 def);

        sf::Int16 get(const std::string& key, const sf::Int16 def);

        sf::Uint16 get(const std::string& key, const sf::Uint16 def);

        sf::Int32 get(const std::string& key, const sf::Int32 def);

        sf::Uint32 get(const std::string& key, const sf::Uint32 def);

        sf::Int64 get(const std::string& key, const sf::Int64 def);

        sf::Uint64 get(const std::string& key, const sf::Uint64 def);

        float get(const std::string& key, const float def);

        double get(const std::string& key, double def);

    protected:
        std::string _path;
        std::unordered_map<std::string, std::string> _map;
        void defaults();
    };
}

#endif //UGAME_CONFIG_H
