#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <vector>

#include "../hpp/game.hpp"
#include "../hpp/gfxMgr.hpp"
#include "../hpp/eventMgr.hpp"
#include "../hpp/eventActions.hpp"
#include "../hpp/eventPredicates.hpp"
#include "../../UI/hpp/ui.hpp"
#include "../hpp/stateMgr.hpp"
#include "../hpp/fontMgr.hpp"
#include "../hpp/AUDIOMGR.HPP"


Game* Game::instance = nullptr;
sf::RenderWindow* Game::window = nullptr;

Game::Game(){
    instance = this;
    gfxmgr = new gfxMgr;
    eventmgr = eventMgr::create();
    statemgr = new stateMgr;
    fontmgr = fontMgr::create();
    audiomgr = new audioMgr;
};

Game::~Game(){

};

void Game::run(){
    init();
    //sf::Event event;
    while (flag_loop)
    {
        begin = std::chrono::steady_clock::now();
        //window events
        if(statemgr->getState()!=nullptr)
        statemgr->getState()->handleEvents(window);
        /*
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
                flag_loop = false;
            }
        }
        */

        //physics
        while (acc >= tpf)
        {
            physics();
            render();
            acc -= tpf;
        }



        //render
        //render();

        end = std::chrono::steady_clock::now();
        acc += (end - begin);
    }

    cleanup();

    return;

};

void Game::physics()
{
    if(statemgr->getState()!=nullptr)
    statemgr->getState()->update();
    //std::cout << "update" << std::endl;
    //std::cout << "Objects size: " << objects.size() << std::endl;
    //if(uphys) uphys(this);
    /*
    for(unsigned int i=0;i<objects.size();i++)
            {
                //std::cout << "update: " << i << std::endl;
                //std::cout << "size "  << objects.size() << std::endl;
                auto el = objects[i];
                if(el!=nullptr)
                {
                    el -> update();
                }
            }
    */
    //Quadtree* tree = new Quadtree(&objects, window, 10); //suboptimal?
    //delete tree;
}

void Game::render()
{
    //std::cout << "render" << std::endl;
    //std::cout << "Texture map size: " << gfxMgr::getMapSize() << std::endl;
    //std::cout << "back: " << objects.back() << std::endl;
    window->clear();
    /*
    for(auto el : objects)
    {
        //std::cout << el << std::endl;
        if(el!=nullptr) window->draw(*el);
    }
    */
    if(statemgr->getState()!=nullptr)
    statemgr->getState()->render(window);
    window->display();
}

void Game::init()
{
    settings.antialiasingLevel = 8;
    window = new sf::RenderWindow(sf::VideoMode(600, 700), "Window", sf::Style::Default, settings);

    //htmlInterpreter hi;
    //hi.loadFromFile("test.html");

    //initDefaultActions(this->eventmgr);
    //initDefaultPredicates(this->eventmgr);

    /*
    int a;
    std::cin >> a;
    */

    //if(uinit) uinit(this);

    flag_loop = true;

    tpf = std::chrono::nanoseconds(1000000000);
    tpf/=fps;

    acc = std::chrono::nanoseconds(0);
}

sf::Window* Game::getWindow(){return window;}
Game* Game::getGame(){return instance;}

void Game::pushState(State* s)
{
    statemgr->pushState(s);
    s->setMgrs(gfxmgr, eventmgr, audiomgr);
}

void Game::popState()
{
    statemgr->popState();
    if(statemgr->getSize() == 0)
    {
        std::cout << "Poped last state" << std::endl;
        stop();
    }
}

State* Game::getState()
{
    return statemgr->getState();
}

void Game::stop()
{
    flag_loop = false;
}

void Game::cleanup()
{
    while(statemgr->getSize() != 0)
    {
        popState();
    }
    delete gfxmgr;
    delete eventmgr;
    delete statemgr;
    delete fontmgr;
    delete audiomgr;
    delete window;
}
