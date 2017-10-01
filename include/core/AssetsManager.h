//
// Created by symbx on 05.08.17.
//

#ifndef UGAME_ASSETSMANAGER_H
#define UGAME_ASSETSMANAGER_H

#include <string>
#include <vector>
#include <SFML/Config.hpp>
#include <SFML/System/InputStream.hpp>
#include <unordered_map>
#include <SFML/Graphics/Font.hpp>

namespace uGame {

    /**
     * Assets manager (unpack resources, download/update from server etc.)
     */
    class AssetsManager {
    public:
        /**
         * Available states
         */
        enum State {
            EMPTY,
            IDLE,
            SCAN,
            PARSE,
            CHECK_INFO,
            UPDATES,
            DOWNLOAD,
            NO_INET,
            NO_PACKAGES,
            BAD_RESP,
            COMPLETE
        };

        /**
         * Package entry
         */
        struct Entry {
            sf::Uint64 offset;
            sf::Uint64 size;
            std::string package;
        };

        /**
         * Download entry
         */
        struct Download {
            sf::Uint16 id;
            sf::Uint64 size;
        };

        /**
         * Initialize manager
         * @param appDir - path to user home + .<gamename>
         */
        static void init(const std::string &appDir);

        /**
         * Cleanup
         */
        static void destroy();

        /**
         * Debug: load resources from files
         * Release: check updates & load resources
         */
        static void run();

        /**
         * Get current state
         * @return current state of manager
         */
        static State getState();

        /**
         * Progress of loading
         * @return progress (0-100)
         */
        static float getProgress();

        /**
         * Check entry exists in resources
         * @param name - path to file
         * @return exists?
         */
        static bool hasEntry(const std::string &name);

        /**
         * Get stream of entry from resources
         * @param name - path to file
         * @return pointer to stream
         */
        static sf::InputStream *getStream(const std::string &name);

    protected:
        static State _state;
        static std::string _dir;
        static std::vector<std::string> _packages;
        static std::vector<Download> _downloads;
        static std::unordered_map<std::string, Entry> _entries;
        static float _progress;

        /**
         * Scan game dir for resources
         */
        static void scan();

        /**
         * Cleanup
         */
        static void clean();

        /**
         * Parse all found resource packages
         */
        static void parse();

        /**
         * Parse one resource package
         * @param file - path to package
         */
        static void read(const std::string &file);

        /**
         * Download all queued packages
         */
        static void download();

        /**
         * Check for resource updates (and add to download queue if exists)
         * @param version - current game || resource version
         */
        static void checkUpdate(const std::string &version);

        /**
         * Check if resource package exists and compare hash with given
         * @param id - id of resource package
         * @param hash - hash of package (from web)
         * @return true if hashes equal else false (not equal or not exists)
         */
        static bool checkHash(sf::Uint16 id, const std::string &hash);

        /**
         * Connect to site (process headers etc.)
         * @param url - url to connect
         * @return connected socket
         */
        static int connect(const std::string &url);
    };
}

#endif //UGAME_ASSETSMANAGER_H
