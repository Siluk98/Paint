#ifndef GAME_H
#define GAME_H

#include <vector>
#include <chrono>
#include "object.hpp"
#include "eventMgr.hpp"


class Game
{
public:
    Game();
    ~Game();
    void run();
    static sf::Window* getWindow();
    static Game* getGame();
    void addObject(Object*);
private:
    static Game* instance;
    void init();
    void physics();
    void render();
    Object* findObject(std::string id);
    std::vector<Object*> objects;
    gfxMgr* gfxmgr;
    eventMgr* eventmgr;

    bool flag_loop;
    const unsigned int fps = 60;
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    std::chrono::nanoseconds acc;
    std::chrono::nanoseconds tpf;
    sf::ContextSettings settings;
    static sf::RenderWindow* window;
};

#endif // GAME_H
