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
#include "../../UI/hpp/ui.hpp"
#include "../hpp/enemyBullet.hpp"

Game* Game::instance = nullptr;
sf::RenderWindow* Game::window = nullptr;
unsigned int Game::memoryAllocated = 0;

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
    window = new sf::RenderWindow(sf::VideoMode(600, 700), "Paint", sf::Style::Default, settings);

    initDefaultActions(this->eventmgr);
    initDefaultPredicates(this, this->eventmgr);

    addObject(new UI::Button("btNew",2,2,"","gfx/btNew.png","gfx/btNewC.png",sf::Color::White,Action{
                                     [](Object* a, Object* b, std::string arg1, std::string arg2){
                                        Game* game = Game::getGame();
                                        //std::cout << "create new canvas" << std::endl;
                                        UI::Canvas* canvas = dynamic_cast<UI::Canvas*>(game->findObject("canvas"));
                                        canvas->clear();
                                     }}));
    addObject(new UI::Button("btLoad",36,2,"","gfx/btLoad.png","gfx/btLoadC.png",sf::Color::White,Action{
                                     [](Object* a, Object* b, std::string arg1, std::string arg2){
                                        Game* game = Game::getGame();
                                        //std::cout << "load from ppm" << std::endl;
                                        UI::Canvas* canvas = dynamic_cast<UI::Canvas*>(game->findObject("canvas"));
                                        canvas->load("pic.png");
                                     }}));
    addObject(new UI::Button("btSave",70,2,"","gfx/btSave.png","gfx/btSaveC.png",sf::Color::White,Action{
                                     [](Object* a, Object* b, std::string arg1, std::string arg2){
                                        Game* game = Game::getGame();
                                        //std::cout << "save as ppm" << std::endl;
                                        UI::Canvas* canvas = dynamic_cast<UI::Canvas*>(game->findObject("canvas"));
                                        canvas->save("pic.png");
                                     }}));

    addObject(new UI::Canvas("canvas", 0,100, 600,600));
    for(int i=0;i<3;i++)
    {
        std::string color="colorbt";
        std::string c="";

        addObject(new UI::Button(color+std::to_string((i*3)+1),104+(i*3+1)*34,2,c+std::to_string(i),"","",sf::Color(0,0,85*(i+1)), Action{
                                    [](Object* a, Object* b, std::string arg1, std::string arg2){
                                        UI::Button* bt = dynamic_cast<UI::Button*>(a);
                                        Game* game = Game::getGame();
                                        UI::Canvas* canvas = dynamic_cast<UI::Canvas*>(game->findObject("canvas"));
                                        std::cout << bt->getText();
                                        canvas->setColor(0,0,85*(std::stoi(bt->getText())+1));
                                        }}));
        addObject(new UI::Button(color+std::to_string((i*3)+2),104+(i*3+2)*34,2,c+std::to_string(i),"","",sf::Color(0,85*(i+1),0), Action{
                                    [](Object* a, Object* b, std::string arg1, std::string arg2){
                                        UI::Button* bt = dynamic_cast<UI::Button*>(a);
                                        Game* game = Game::getGame();
                                        UI::Canvas* canvas = dynamic_cast<UI::Canvas*>(game->findObject("canvas"));
                                        std::cout << bt->getText();
                                        canvas->setColor(0,85*(std::stoi(bt->getText())+1),0);
                                        }}));
        addObject(new UI::Button(color+std::to_string(i*3),104+(i*3)*34,2,c+std::to_string(i),"","",sf::Color(85*(i+1),0,0), Action{
                                    [](Object* a, Object* b, std::string arg1, std::string arg2){
                                        UI::Button* bt = dynamic_cast<UI::Button*>(a);
                                        Game* game = Game::getGame();
                                        UI::Canvas* canvas = dynamic_cast<UI::Canvas*>(game->findObject("canvas"));
                                        std::cout << bt->getText();
                                        canvas->setColor(85*(std::stoi(bt->getText())+1),0,0);
                                        }}));
    }

    addObject(new UI::Button("brushUp",550,2,"","gfx/btBrushUp.png","gfx/btBrushUp.png",sf::Color::White,Action{
                                [](Object* a, Object* b, std::string arg1, std::string arg2){
                                    Game* game = Game::getGame();
                                    UI::Canvas* canvas = dynamic_cast<UI::Canvas*>(game->findObject("canvas"));
                                    canvas->brushUp();
                                }
                             }));

    addObject(new UI::Button("brushDown",550,36,"","gfx/btBrushDown.png","gfx/btBrushDown.png",sf::Color::White,Action{
                                [](Object* a, Object* b, std::string arg1, std::string arg2){
                                    Game* game = Game::getGame();
                                    UI::Canvas* canvas = dynamic_cast<UI::Canvas*>(game->findObject("canvas"));
                                    canvas->brushDown();
                                }
                             }));

    //UI::cssHandler* css = new UI::cssHandler;
    //css -> loadFromFile("aaa.txt");
    //addObject(new UI::Button("test", *css));

    //objects.push_back(new EnemyBullet(sf::Vector2f(300,200),&objects));
    //objects.push_back(new testObj(500, sf::Color(232,123,130)));

    flag_loop = true;

    tpf = std::chrono::nanoseconds(1000000000);
    tpf/=fps;

    acc = std::chrono::nanoseconds(0);
}

sf::Window* Game::getWindow(){return window;}
Game* Game::getGame(){return instance;}
Object* Game::findObject(std::string id)
{
    for(Object* e:objects)
    {
        if(e->getId() == id) return e;
    }
    return nullptr;
}

void Game::addObject(Object* obj)
{
    if(findObject(obj->getId())==nullptr)
    {
        objects.push_back(obj);
        memoryAllocated += sizeof(*obj);
        std::cout << "Memory allocated: " << memoryAllocated << std::endl;
    }

}
