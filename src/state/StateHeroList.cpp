//
// Created by symbx on 01.10.17.
//

#include <core/Lang.h>
#include <core/AssetsManager.h>
#include <core/Application.h>
#include <utils/Logger.h>
#include <state/StatePlay.h>
#include "state/StateHeroList.h"

namespace uGame {

    StateHeroList::StateHeroList() :
        _bgTexture(),
        _bg() {

    }

    StateHeroList::~StateHeroList() {
        delete _menuFrame;
    }

    void StateHeroList::init(const Application *app) {
        _app = const_cast<Application *>(app);
        sf::InputStream *stream = AssetsManager::getStream("/imgs/ui/main_bg.jpg");
        if(!_bgTexture.loadFromStream(*stream))
            L_WARN("Texture not load!");
        _bg.setTexture(_bgTexture);
        delete stream;
        _menuFrame = new Window(Lang::get(12));
        centerContent(app->window()->getSize());
    }

    void StateHeroList::event(const sf::Event &event) {
        if (event.type == sf::Event::Resized) {
            sf::Vector2u wsize(event.size.width, event.size.height);
            centerContent(wsize);
        }

        if(_menuFrame != NULL && _menuFrame->event(event))
            return;

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                _app->state()->close();
            if (event.key.code == sf::Keyboard::Space)
                _app->state()->open(new StatePlay());
        }
    }

    void StateHeroList::update(const float time) {
        _menuFrame->update(time);
    }

    void StateHeroList::draw(sf::RenderWindow &render) {
        render.draw(_bg);
        render.draw(*_menuFrame);
    }

    void StateHeroList::centerContent(sf::Vector2u wsize) {
        sf::FloatRect bgsize = _bg.getLocalBounds();
        _bg.setOrigin(bgsize.width/2, bgsize.height/2);
        _bg.setPosition(wsize.x/2, wsize.y/2);
        float ratio = bgsize.width/bgsize.height;
        if((wsize.x/wsize.y) >= ratio) {
            _bg.setScale((bgsize.height/wsize.y)*ratio, bgsize.height/wsize.y);
        }else{
            _bg.setScale(bgsize.width/wsize.x, (bgsize.width/wsize.x)*ratio);
        }

        sf::FloatRect fsize = _menuFrame->getLocalBounds();
        _menuFrame->setPosition((wsize.x-fsize.width)/2, (wsize.y-fsize.height)/2);
    }
}