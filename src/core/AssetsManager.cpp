//
// Created by symbx on 05.08.17.
//

#include <utils/Utils.h>
#include <cstring>
#include <unistd.h>
#include <SFML/Network/Http.hpp>
#include <SFML/System/FileInputStream.hpp>
#include <sstream>
#include <netdb.h>
#include <core/PackageStream.h>
#include <core/Lang.h>
#include <gui/UI.h>
#include "core/AssetsManager.h"
#include "utils/Logger.h"
#include "Constants.h"

namespace uGame {

    std::string AssetsManager::_dir;
    std::vector<std::string> AssetsManager::_packages;
    std::unordered_map<std::string, AssetsManager::Entry> AssetsManager::_entries;
    std::vector<AssetsManager::Download> AssetsManager::_downloads;
    AssetsManager::State AssetsManager::_state = AssetsManager::EMPTY;
    float AssetsManager::_progress = 0;

    void AssetsManager::init(const std::string &appDir) {
        AssetsManager::_dir = appDir;
        L_INFO("Initialize AssetsManager");
#ifdef _DEBUG
        AssetsManager::_dir.append(GAME_RES_DIR);
#else
        AssetsManager::_dir.append(GAME_RES_FILE);
#endif
        AssetsManager::_state = EMPTY;
    }

    void AssetsManager::destroy() {
        AssetsManager::clean();
    }

    void AssetsManager::scan() {
        L_INFO("Scan " + _dir + " for packages");
        AssetsManager::_state = SCAN;
        for (int i = 0; i < PACK_MAX; ++i) {
            std::string file(AssetsManager::_dir + std::to_string(i) + GAME_RES_EXT);
            if (!Utils::isFileExists(file))
                break;
            L_INFO("Found " + file);
            AssetsManager::_packages.insert(AssetsManager::_packages.begin(), file);
        }
        AssetsManager::_state = _packages.empty() ? NO_PACKAGES : IDLE;
    }

    void AssetsManager::parse() {
        if (AssetsManager::_packages.empty())
            return;
        L_INFO("Parsing packages");
        AssetsManager::_state = PARSE;
        AssetsManager::clean();
        AssetsManager::_progress = 0;
        float perFile = 100.0f / AssetsManager::_packages.size();
        while (!AssetsManager::_packages.empty()) {
            read(AssetsManager::_packages.back());
            AssetsManager::_packages.pop_back();
            AssetsManager::_progress += perFile;
        }
        AssetsManager::_state = IDLE;
    }

    void AssetsManager::clean() {
        AssetsManager::_entries.clear();
        UI::clean();
    }

    void AssetsManager::read(const std::string &file) {
        L_INFO("Read " + file);
        std::ifstream stream(file, std::ifstream::binary);
        char head[4];
        stream.read(&head[0], 4);
        if (head[0] != 'G' || head[1] != 'R' || head[2] != 'P' || head[3] != 'F') {
            L_WARN("Incorrect header, skip file");
            return;
        }

        sf::Uint32 count;
        stream.read((char *) &count, sizeof(sf::Uint32));

        unsigned char nameLen;
        char *buffer = new char[256];
        std::string name;
        for (int i = 0; i < count; ++i) {
            struct Entry entry;
            stream.read((char *) &nameLen, 1);
            memset(buffer, 0, 256);
            stream.read(buffer, nameLen);
            name.assign(buffer, nameLen);
            entry.package = file;
            stream.read((char *) &entry.offset, sizeof(sf::Uint64));
            stream.read((char *) &entry.size, sizeof(sf::Uint64));
            AssetsManager::_entries[name] = entry;
            //L_INFO("Add entry "+name+" at "+std::to_string(entry.offset)+" with size "+std::to_string(entry.size));
        }
        L_INFO("Loaded " + std::to_string(count) + " entries");
        delete[] buffer;
    }

    void AssetsManager::run() {
#ifndef _DEBUG
        std::string version(GAME_VERS);
        AssetsManager::scan();
        if (AssetsManager::_state != NO_PACKAGES) {
            AssetsManager::parse();
            if (AssetsManager::hasEntry(GAME_VERS_FILE)) {
                sf::InputStream *stream = AssetsManager::getStream(GAME_VERS_FILE);
                char buffer[8];
                sf::Int64 len = stream->read((char *) buffer, 8);
                version.assign(buffer, static_cast<unsigned long>(len));
                delete stream;
            }
        } else
            L_WARN("No packages available");
        AssetsManager::checkUpdate(version);
        if (_state == UPDATES && !_downloads.empty()) {
            L_INFO("Has files to download");
            AssetsManager::download();
            AssetsManager::clean();
            AssetsManager::scan();
            AssetsManager::parse();
        }
        UI::loadFonts();
        Lang::load();
        if (AssetsManager::_state == IDLE)
            AssetsManager::_state = COMPLETE;
#else
        UI::loadFonts();
        Lang::load();
        AssetsManager::_state = COMPLETE;
#endif
    }

    AssetsManager::State AssetsManager::getState() {
        return AssetsManager::_state;
    }

    float AssetsManager::getProgress() {
        if (AssetsManager::_progress > 100.0f)
            return 100.0f;
        return AssetsManager::_progress;
    }

    void AssetsManager::download() {
        if (AssetsManager::_downloads.empty())
            return;
        AssetsManager::_state = DOWNLOAD;
        float perFile = 100.0f / AssetsManager::_downloads.size();
        AssetsManager::_progress = 0;
        float last;
        while (!AssetsManager::_downloads.empty()) {
            last = AssetsManager::_progress;
            float current = 0;
            struct Download d = AssetsManager::_downloads.back();
            AssetsManager::_downloads.pop_back();
            std::string web(GAME_SITE_RES + std::to_string(d.id) + GAME_RES_EXT);
            std::string local(AssetsManager::_dir + std::to_string(d.id) + GAME_RES_EXT);
            L_INFO("Start " + web + " -> " + local);
            int sock = connect(web);
            if (sock < 1) {
                L_ERR("Not connected!");
                AssetsManager::_state = NO_INET;
                return;
            }
            bool headerEnd = false;
            sf::Int64 fileLen = 0;
            sf::Int64 loadLen = 0;
            char *buffer[1024];
            std::ofstream file(local, std::ofstream::binary);
            while (1) {
                ssize_t r = recv(sock, buffer, 1024, 0);
                if (r == 0)
                    break;
                if (headerEnd) {
                    file.write((char *) buffer, r);
                    loadLen += r;
                    current = (loadLen / (float) fileLen) * perFile;
                } else {
                    std::string tmp((char *) buffer, r);
                    unsigned long pos = tmp.find("Content-Length");
                    if (pos != std::string::npos) {
                        fileLen = std::stoll(tmp.substr(pos + 15, tmp.find("\r\n", pos + 15) - pos - 15));
                        L_INFO("File size: " + std::to_string(fileLen));
                    }
                    pos = tmp.find("\r\n\r\n");
                    if (pos != std::string::npos) {
                        headerEnd = true;
                        file.write((char *) buffer + pos + 4, r - pos - 4);
                        loadLen = static_cast<sf::Int64>(r - pos - 4);
                        current = (loadLen / (float) fileLen) * perFile;
                    }
                }
                AssetsManager::_progress = current + last;
            }
            close(sock);
            file.flush();
            file.close();
        }
        AssetsManager::_state = IDLE;
    }

    void AssetsManager::checkUpdate(const std::string &version) {
        L_INFO("Version check... (" + version + ')');
        AssetsManager::_state = CHECK_INFO;
        sf::Http http(GAME_SITE_HOST, GAME_SITE_PORT);
        sf::Http::Request req(GAME_SITE_UPD);
        std::string cnt("Connect to ");
        cnt.append(GAME_SITE_HOST);
        cnt.append(':' + std::to_string(GAME_SITE_PORT) + '/');
        cnt.append(GAME_SITE_UPD);
        L_INFO(cnt);
        req.setField("Game-Version", version);
        sf::Http::Response resp = http.sendRequest(req, sf::seconds(30.0f));
        if (resp.getStatus() != sf::Http::Response::Ok) {
            AssetsManager::_state = resp.getStatus() < 1000 ? BAD_RESP : NO_INET;
            L_ERR("No connection or bad response! ("+std::to_string(resp.getStatus())+')');
            return;
        }
        std::string body = resp.getBody();
        if (body.length() % 40 != 0) {
            AssetsManager::_state = BAD_RESP;
            L_ERR("Bad response! (len: " + std::to_string(body.length()) + ')');
            L_ERR(body);
            return;
        }
        std::stringstream stream;
        stream.write(body.c_str(), body.length());
        char buffer[32];
        std::string hash;
        sf::Uint64 size;
        L_INFO("Read response");
        for (sf::Uint16 i = 0; i < body.length() / 40; i++) {
            stream.read(reinterpret_cast<char *>(buffer), 32);
            hash.assign(buffer, 32);
            L_INFO("Package " + std::to_string(i) + " with hash " + hash);
            stream.read(reinterpret_cast<char *>(&size), sizeof(sf::Uint64));
            if (!checkHash(i, hash)) {
                struct Download d;
                d.id = i;
                d.size = size;
                AssetsManager::_downloads.insert(AssetsManager::_downloads.begin(), d);
            }
        }
        AssetsManager::_state = AssetsManager::_downloads.empty() ? IDLE : UPDATES;
    }

    bool AssetsManager::hasEntry(const std::string &name) {
#ifdef _DEBUG
        return Utils::isFileExists(AssetsManager::_dir + name);
#else
        return AssetsManager::_entries.count(name) > 0;
#endif
    }

    sf::InputStream *AssetsManager::getStream(const std::string &name) {
#ifdef _DEBUG
        std::string file(AssetsManager::_dir + name);
        if(!Utils::isFileExists(file)) {
            L_ERR("Not have "+name+" in resources!");
            return NULL;
        }
        sf::FileInputStream* stream = new sf::FileInputStream();
        stream->open(file);
        return stream;
#else
        if(!hasEntry(name)) {
            L_ERR("Not have "+name+" in resources!");
            return NULL;
        }
        struct Entry entry = AssetsManager::_entries[name];
        return new PackageStream(entry.package, entry.offset, entry.size);
#endif
    }

    bool AssetsManager::checkHash(sf::Uint16 id, const std::string &hash) {
        L_INFO("Check hash");
        std::string file = AssetsManager::_dir + std::to_string(id) + GAME_RES_EXT;
        if (!Utils::isFileExists(file)) {
            L_WARN("File not exists!");
            return false;
        }
        std::string local = Utils::hashFile(file);
        L_INFO("Hash: local " + local + " remote " + hash);
        return hash == local;
    }

    int AssetsManager::connect(const std::string &url) {
        struct addrinfo hints;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        struct addrinfo *info;
        if (getaddrinfo(GAME_SITE_HOST, std::to_string(GAME_SITE_PORT).c_str(), &hints, &info) != 0) {
            return -1;
        }
        int sock = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
        if (sock <= 0) {
            return -1;
        }
        if (::connect(sock, info->ai_addr, info->ai_addrlen) != 0) {
            return -1;
        }
        freeaddrinfo(info);
        //Request
        std::string req("GET " + url + " HTTP/1.0\r\n");
        req.append("Host: ");
        req.append(GAME_SITE_HOST);
        req.append("\r\n");
        req.append("Connection: close\r\n\r\n");
        send(sock, req.c_str(), req.length(), 0);
        return sock;
    }
}
