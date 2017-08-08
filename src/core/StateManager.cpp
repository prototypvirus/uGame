//
// Created by symbx on 08.08.17.
//

#include "core/StateManager.h"

StateManager::StateManager(Application *app) :
    _states() {
    _app = app;
}

StateManager::~StateManager() {
    clean();
}

void StateManager::init() {
    //Add loading state
}

void StateManager::clean() {
    while (!_states.empty()) {
        delete _states.back();
        _states.pop_back();
    }
}

void StateManager::open(GameState *state) {
    state->init(_app);
    _states.push_back(state);
}

void StateManager::close() {
    if(!_states.empty()) {
        delete _states.back();
        _states.pop_back();
    }
    if(_states.empty())
        _app->quit();
}

void StateManager::event(const sf::Event &event) {
    /*for(auto& i : _states) {
        if(i->isPassiveEvent())
            i->event(event);
    }*/
    if(!_states.empty())
        _states.back()->event(event);
}

void StateManager::update(const float time) {
    /*for(auto& i : _states) {
        if(i->isPassiveUpdate())
            i->update(time);
    }*/
    if(!_states.empty())
        _states.back()->update(time);
}

void StateManager::draw(const sf::RenderWindow &render, const float time) {
    /*for(auto& i : _states) {
        if(i->isPassiveDraw())
            i->draw(render, time);
    }*/
    if(!_states.empty())
        _states.back()->draw(render, time);
}
