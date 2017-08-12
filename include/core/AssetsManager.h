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

namespace uGame {

    class AssetsManager {
    public:
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
        struct Entry {
            sf::Uint64 offset;
            sf::Uint64 size;
            std::string package;
        };
        struct Download {
            sf::Uint16 id;
            sf::Uint64 size;
        };

        static void init(const std::string &appDir);

        static void destroy();

        static void run();

        static State getState();

        static float getProgress();

        static bool hasEntry(const std::string &name);

        static sf::InputStream *getStream(const std::string &name);

    protected:
        static State _state;
        static std::string _dir;
        static std::vector<std::string> _packages;
        static std::vector<Download> _downloads;
        static std::unordered_map<std::string, Entry> _entries;
        static float _progress;

        static void scan();

        static void clean();

        static void parse();

        static void read(const std::string &file);

        static void download();

        static void checkUpdate(const std::string &version);

        static bool checkHash(sf::Uint16 id, const std::string &hash);

        static int connect(const std::string &url);
    };
}

#endif //UGAME_ASSETSMANAGER_H
