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
        BAD_RESP
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
    AssetsManager(const std::string& appDir);
    ~AssetsManager();
    void run();
    State getState();
    float getProgress();
    bool hasEntry(const std::string& name);
    sf::InputStream* getStream(const std::string& name);

protected:
    State _state;
    std::string _dir;
    std::vector<std::string> _packages;
    std::vector<Download> _downloads;
    std::unordered_map<std::string, Entry> _entries;
    float _progress;
    void scan();
    void parse();
    void clean();
    void read(const std::string& file);
    void download();
    void checkUpdate(const std::string& version);
    bool checkHash(sf::Uint16 id, const std::string& hash);
    int connect(const std::string& url);
};


#endif //UGAME_ASSETSMANAGER_H
