#ifndef GAME_H
#define GAME_H

#include <vector>
#include <chrono>
#include "object.hpp"
#include "eventMgr.hpp"
#include "stateMgr.hpp"
#include "fontMgr.hpp"
#include "AUDIOMGR.HPP"


class Game
{
public:
    Game();
    ~Game();
    void run();
    void stop();
    static sf::Window* getWindow();
    static Game* getGame();
    void pushState(State*);
    void popState();
    State* getState();
private:
    static Game* instance;

    void init();
    void physics();
    void render();
    void cleanup();
    gfxMgr* gfxmgr;
    eventMgr* eventmgr;
    stateMgr* statemgr;
    fontMgr* fontmgr;
    audioMgr* audiomgr;

    bool flag_loop;
    State* currentState;
    const unsigned int fps = 60;
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    std::chrono::nanoseconds acc;
    std::chrono::nanoseconds tpf;
    sf::ContextSettings settings;
    static sf::RenderWindow* window;
};

#endif // GAME_H
