//
// Created by symbx on 08.08.17.
//

#include <algorithm>
#include <SFML/System/InputStream.hpp>
#include <utils/Logger.h>
#include <state/StateMenu.h>
#include <Constants.h>
#include "core/AssetsManager.h"
#include "state/StateLoading.h"

namespace uGame {

    StateLoading::StateLoading() {

    }

    StateLoading::~StateLoading() {
        delete _logo;
        delete _logoTexture;
        delete _progressBack;
        delete _progress;
        delete _loadText;
        delete _font;
        _work->terminate();
        delete _work;
    }

    void StateLoading::init(const Application *app) {
        _app = const_cast<Application *>(app);
        _logoTexture = new sf::Texture();
        _logoTexture->loadFromFile("symbx.png");
        _logoTexture->setSmooth(true);
        _logo = new sf::Sprite(*_logoTexture);
        sf::Color base(18, 49, 84);
        _progressBack = new sf::RectangleShape();
        _progressBack->setOutlineColor(base);
        _progressBack->setOutlineThickness(2.0f);
        _progress = new sf::RectangleShape();
        _progress->setSize(sf::Vector2f(10, 20));
        _progress->setFillColor(base);
        _font = new sf::Font();
        _font->loadFromFile(FALLBACK_FONT);
        _loadText = new sf::Text();
        _loadText->setFont(*_font);
        _loadText->setCharacterSize(20);
        _loadText->setString("Loading...");
        _loadText->setFillColor(base);
        centerContent(app->window()->getSize());
        _work = new sf::Thread(&AssetsManager::run);
        _work->launch();
    }

    void StateLoading::update(const float time) {
        _progressVisible = false;
        switch (AssetsManager::getState()) {
            case AssetsManager::IDLE:
                setText("Wait...");
                break;
            case AssetsManager::CHECK_INFO:
                setText("Check for updates...");
                break;
            case AssetsManager::SCAN:
                setText("Looking local resources...");
                _progressVisible = false;
                break;
            case AssetsManager::DOWNLOAD:
                setText("Downloading resources...");
                _progressVisible = true;
                setProgress(AssetsManager::getProgress());
                break;
            case AssetsManager::UPDATES:
                setText("Prepare downloading");
                break;
            case AssetsManager::PARSE:
                setText("Reading resources...");
                _progressVisible = true;
                setProgress(AssetsManager::getProgress());
                break;
            case AssetsManager::NO_INET:
                setText("Can't connecto to site.");
                break;
            case AssetsManager::NO_PACKAGES:
                setText("Not found local resources");
                break;
            case AssetsManager::COMPLETE:
                _app->state()->replace(new StateMenu());
                break;
            default:
                setText("Hmm...unknown state...");
                break;
        }
    }

    void StateLoading::event(const sf::Event &event) {
    }

    void StateLoading::draw(sf::RenderWindow &render) {
        render.clear(sf::Color::White);
        render.draw(*_logo);
        if (_progressVisible) {
            render.draw(*_progressBack);
            render.draw(*_progress);
        }
        render.draw(*_loadText);
    }

    void StateLoading::centerContent(sf::Vector2u wsize) {
        sf::Vector2u lsize = _logoTexture->getSize();
        sf::Uint32 xpos = (wsize.x - lsize.x) / 2;
        sf::Uint32 ypos = (wsize.y - lsize.y) / 2;
        _logo->setPosition(xpos, ypos);
        _progressBack->setSize(sf::Vector2f(lsize.x + 4.0f, 24.0f));
        _progressBack->setPosition(xpos - 2, ypos + lsize.y + 40);
        _progress->setPosition(xpos, ypos + lsize.y + 42);
        centerText(wsize);
    }

    void StateLoading::centerText(sf::Vector2u wsize) {
        sf::FloatRect rect = _loadText->getGlobalBounds();
        sf::Vector2u lsize = _logoTexture->getSize();
        _loadText->setPosition((wsize.x - rect.width) / 2, (wsize.y - lsize.y) / 2 + lsize.y + 10);
    }

    void StateLoading::setProgress(float val) {
        sf::Vector2u r = _logoTexture->getSize();
        _progress->setSize(sf::Vector2f(r.x * (val / 100), 20));
    }

    void StateLoading::setText(const std::string &msg) {
        _loadText->setString(msg);
        centerText(_app->window()->getSize());
    }

    void StateLoading::resize(int w, int h) {
        centerContent(sf::Vector2u(w, h));
    }
}