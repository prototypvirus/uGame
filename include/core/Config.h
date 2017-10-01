//
// Created by symbx on 27.08.17.
//

#ifndef UGAME_CONFIG_H
#define UGAME_CONFIG_H

#include <string>
#include <SFML/Config.hpp>
#include <unordered_map>

namespace uGame {
    /**
     * Configuration class
     */
    class Config {
    public:
        /**
         * Constructor
         * @param filename - path to configuration file
         */
        Config(const std::string &filename);

        virtual ~Config();

        /**
         * Load configuration from file
         */
        void load();

        /**
         * Save configuration to file
         */
        void save();

        /**
         * Get item (string)
         * @param key - key of setting
         * @param def - default value
         * @return saved value or default
         */
        std::string get(const std::string& key, const std::string& def);

        /**
         * Get item (int8)
         * @param key - key of setting
         * @param def - default value
         * @return saved value or default
         */
        sf::Int8 get(const std::string& key, const sf::Int8 def);

        /**
         * Get item (uint8)
         * @param key - key of setting
         * @param def - default value
         * @return saved value or default
         */
        sf::Uint8 get(const std::string& key, const sf::Uint8 def);

        /**
         * Get item (int16)
         * @param key - key of setting
         * @param def - default value
         * @return saved value or default
         */
        sf::Int16 get(const std::string& key, const sf::Int16 def);


        /**
         * Get item (uint16)
         * @param key - key of setting
         * @param def - default value
         * @return saved value or default
         */
        sf::Uint16 get(const std::string& key, const sf::Uint16 def);

        /**
         * Get item (int32)
         * @param key - key of setting
         * @param def - default value
         * @return saved value or default
         */
        sf::Int32 get(const std::string& key, const sf::Int32 def);

        /**
         * Get item (uint32)
         * @param key - key of setting
         * @param def - default value
         * @return saved value or default
         */
        sf::Uint32 get(const std::string& key, const sf::Uint32 def);

        /**
         * Get item (int64)
         * @param key - key of setting
         * @param def - default value
         * @return saved value or default
         */
        sf::Int64 get(const std::string& key, const sf::Int64 def);

        /**
         * Get item (uint64)
         * @param key - key of setting
         * @param def - default value
         * @return saved value or default
         */
        sf::Uint64 get(const std::string& key, const sf::Uint64 def);

        /**
         * Get item (float)
         * @param key - key of setting
         * @param def - default value
         * @return saved value or default
         */
        float get(const std::string& key, const float def);

        /**
         * Get item (double)
         * @param key - key of setting
         * @param def - default value
         * @return saved value or default
         */
        double get(const std::string& key, double def);

    protected:
        std::string _path;
        std::unordered_map<std::string, std::string> _map;

        /**
         * Init empty file with defaults values
         */
        void defaults();
    };
}

#endif //UGAME_CONFIG_H
