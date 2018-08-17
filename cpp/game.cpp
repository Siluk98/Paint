#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <vector>

#include "../hpp/game.hpp"
#include "../hpp/gfxMgr.hpp"
#include "../hpp/background.hpp"
#include "../hpp/testobj.hpp"
#include "../hpp/eventMgr.hpp"
#include "../hpp/eventActions.hpp"
#include "../hpp/eventPredicates.hpp"
#include "../hpp/quadtree.hpp"
#include "../lib/UI/hpp/ui.hpp"
#include "../hpp/enemyBullet.hpp"

Game* Game::instance = nullptr;

Game::Game(){
    instance = this;
    gfxmgr = new gfxMgr;
    eventmgr = new eventMgr;
};

Game::~Game(){};

void Game::run(){
    init();


    sf::Event event;
    while (flag_loop)
    {
        begin = std::chrono::steady_clock::now();
        //window events
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
                flag_loop = false;
            }
        }

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

    return;

};

void Game::physics()
{
    //std::cout << "update" << std::endl;
    //std::cout << "Objects size: " << objects.size() << std::endl;
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
    //Quadtree* tree = new Quadtree(&objects, window, 10); //suboptimal?
    //delete tree;
}

void Game::render()
{
    //std::cout << "render" << std::endl;
    //std::cout << "Texture map size: " << gfxMgr::getMapSize() << std::endl;
    //std::cout << "back: " << objects.back() << std::endl;
    window->clear();
    for(auto el : objects)
    {
        //std::cout << el << std::endl;
        if(el!=nullptr) window->draw(*el);
    }
    window->display();
}

void Game::init()
{
    settings.antialiasingLevel = 8;
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "Town Builder", sf::Style::Default, settings);

    initDefaultActions(this->eventmgr);
    initDefaultPredicates(this, this->eventmgr);

    for(int i=1;i<4;i++)
    {
        std::string id = "bt";
        id+=std::to_string(i);
        objects.push_back(new UI::Button(id,100*i, 100*i,"gfx/emptySlot.png","gfx/placeholder.png"));
        //objects.push_back(new Background(100*i,100*i,true));
    }

    //objects.push_back(new EnemyBullet(sf::Vector2f(300,200),&objects));
    objects.push_back(new testObj(500, sf::Color(232,123,130)));

    flag_loop = true;

    tpf = std::chrono::nanoseconds(1000000000);
    tpf/=fps;

    acc = std::chrono::nanoseconds(0);
}

sf::Window* Game::getWindow(){return window;}
Game* Game::getGame(){return instance;}
