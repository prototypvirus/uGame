//
// Created by symbx on 27.08.17.
//

#include <core/Lang.h>
#include "state/StateSignIn.h"
#include "core/Application.h"

namespace uGame {

    StateSignIn::StateSignIn() {}

    StateSignIn::~StateSignIn() {
        delete _bgTexture;
        delete _bg;
        delete _menuFrame;
        delete _labelUser;
        delete _labelPass;
        delete _enterBtn;
        delete _backBtn;
        delete _userInput;
        delete _passInput;
    }

    void StateSignIn::init(const Application *app) {
        _app = const_cast<Application *>(app);
        _bgTexture = new sf::Texture();
        sf::InputStream *stream = AssetsManager::getStream("/imgs/ui/main_bg.jpg");
        _bgTexture->loadFromStream(*stream);
        _bg = new sf::Sprite();
        _bg->setTexture(*_bgTexture);
        delete stream;
        _menuFrame = new Window(Lang::get(6));
        int w = _menuFrame->getLocalBounds().width;
        _labelUser = new Label(Lang::get(8), w);
        _labelPass = new Label(Lang::get(9), w);
        _enterBtn = new Button(Lang::get(10));
        _backBtn = new Button(Lang::get(11));
        _userInput = new InputBox(w - 20);
        _passInput = new InputBox(w - 20);
        _menuFrame->addControl(_labelUser);
        _menuFrame->addControl(_labelPass);
        _menuFrame->addControl(_enterBtn);
        _menuFrame->addControl(_backBtn);
        _menuFrame->addControl(_userInput);
        _menuFrame->addControl(_passInput);
        _userInput->focus();
        centerContent(app->window()->getSize());
    }

    void StateSignIn::event(const sf::Event &event) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                _app->state()->close();
        }
        if (event.type == sf::Event::Resized) {
            sf::Vector2u wsize(event.size.width, event.size.height);
            centerContent(wsize);
        }
        if(_menuFrame != NULL)
            _menuFrame->event(event);
    }

    void StateSignIn::update(const float time) {
        _menuFrame->update(time);
        if(_menuFrame->isClose())
            _app->state()->close();
    }

    void StateSignIn::draw(sf::RenderWindow &render) {
        render.draw(*_bg);
        render.draw(*_menuFrame);
    }

    void StateSignIn::centerContent(sf::Vector2u wsize) {
        sf::FloatRect bgsize = _bg->getLocalBounds();
        _bg->setOrigin(bgsize.width/2, bgsize.height/2);
        _bg->setPosition(wsize.x/2, wsize.y/2);
        float ratio = bgsize.width/bgsize.height;
        if((wsize.x/wsize.y) >= ratio) {
            _bg->setScale((bgsize.height/wsize.y)*ratio, bgsize.height/wsize.y);
        }else{
            _bg->setScale(bgsize.width/wsize.x, (bgsize.width/wsize.x)*ratio);
        }
        sf::FloatRect fsize = _menuFrame->getLocalBounds();
        _menuFrame->setPosition((wsize.x-fsize.width)/2, (wsize.y-fsize.height)/2);

        sf::FloatRect btn = _enterBtn->getLocalBounds();
        _labelUser->setPosition(0, 92);
        _labelPass->setPosition(0, 144);
        _enterBtn->setPosition((fsize.width - btn.width)/2, 92+btn.height*2);
        _backBtn->setPosition((fsize.width - btn.width)/2, 92+btn.height*3);
        _userInput->setPosition(10, 120);
        _passInput->setPosition(10, 172);
    }
}