//
// Created by symbx on 08.08.17.
//

#ifndef UGAME_STATEMANAGER_H
#define UGAME_STATEMANAGER_H


#include "GameState.h"

class Application;

class StateManager {
public:
    StateManager(Application* app);
    ~StateManager();
    void init();
    void clean();
    void open(GameState* state);
    void close();
    void event(const sf::Event& event);
    void update(const float time);
    void draw(sf::RenderWindow& render, const float time);

protected:
    Application* _app;
    std::vector<GameState*> _states;
};


#endif //UGAME_STATEMANAGER_H
