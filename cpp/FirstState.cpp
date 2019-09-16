#include "../hpp/firstState.hpp"
#include <iostream>
#include "../lib/Engine/hpp/game.hpp"
#include "../lib/UI/hpp/button.hpp"
#include "../lib/UI/hpp/canvas.hpp"
#include "../lib/UI/hpp/input.hpp"
#include "../lib/Engine/hpp/AUDIOMGR.HPP"
//#include "../lib/Engine/hpp/eventPredicates.hpp"

FirstState::FirstState(gfxMgr* g,eventMgr* e, audioMgr* a)
{
    std::cout << "FirstState: const" << std::endl;
    gfxmgr = g;
    eventmgr = e;
    audiomgr = a;
    if(cssmgr == nullptr)
        cssmgr = new UI::cssMgr();
    //initDefaultPredicates(e);
}

FirstState::FirstState()
{
    std::cout << "FirstState: const" << std::endl;
    gfxmgr = nullptr;
    eventmgr = eventMgr::getInstance();
    if(cssmgr == nullptr)
        cssmgr = new UI::cssMgr();
    audiomgr = new audioMgr();
}

FirstState::~FirstState()
{
    std::cout << "FirstState: delete" << std::endl;
}

void FirstState::init()
{
    std::cout << "FirstState: init" << std::endl;
    eventmgr = eventMgr::getInstance();
    std::cout << eventmgr << std::endl;
    //initDefaultPredicates(eventmgr);
    //eventmgr->printPredicates();


    addObject(new UI::Button("btNew",2,2,"","gfx/btNew.png","gfx/btNewC.png",sf::Color::White,Action{
                                     [](Object* a, Object* b, std::string arg1, std::string arg2){
                                        Game* game = Game::getGame();
                                        State* s = game->getState();
                                        //std::cout << "create new canvas" << std::endl;
                                        UI::Canvas* canvas = dynamic_cast<UI::Canvas*>(s->findObject("canvas"));
                                        canvas->clear();
                                     }}));
    addObject(new UI::Button("btLoad",36,2,"","gfx/btLoad.png","gfx/btLoadC.png",sf::Color::White,Action{
                                     [](Object* a, Object* b, std::string arg1, std::string arg2){
                                        Game* game = Game::getGame();
                                        State* s = game->getState();
                                        //std::cout << "load from ppm" << std::endl;
                                        UI::Canvas* canvas = dynamic_cast<UI::Canvas*>(s->findObject("canvas"));
                                        canvas->load("pic.png");
                                     }}));
    addObject(new UI::Button("btSave",70,2,"","gfx/btSave.png","gfx/btSaveC.png",sf::Color::White,Action{
                                     [](Object* a, Object* b, std::string arg1, std::string arg2){
                                        Game* game = Game::getGame();
                                        State* s = game->getState();
                                        //std::cout << "save as ppm" << std::endl;
                                        UI::Canvas* canvas = dynamic_cast<UI::Canvas*>(s->findObject("canvas"));
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
                                        State* s = game->getState();
                                        UI::Canvas* canvas = dynamic_cast<UI::Canvas*>(s->findObject("canvas"));
                                        std::cout << bt->getText();
                                        canvas->setColor(0,0,85*(std::stoi(bt->getText())+1));
                                        }}));
        addObject(new UI::Button(color+std::to_string((i*3)+2),104+(i*3+2)*34,2,c+std::to_string(i),"","",sf::Color(0,85*(i+1),0), Action{
                                    [](Object* a, Object* b, std::string arg1, std::string arg2){
                                        UI::Button* bt = dynamic_cast<UI::Button*>(a);
                                        Game* game = Game::getGame();
                                        State* s = game->getState();
                                        UI::Canvas* canvas = dynamic_cast<UI::Canvas*>(s->findObject("canvas"));
                                        std::cout << bt->getText();
                                        canvas->setColor(0,85*(std::stoi(bt->getText())+1),0);
                                        }}));
        addObject(new UI::Button(color+std::to_string(i*3),104+(i*3)*34,2,c+std::to_string(i),"","",sf::Color(85*(i+1),0,0), Action{
                                    [](Object* a, Object* b, std::string arg1, std::string arg2){
                                        UI::Button* bt = dynamic_cast<UI::Button*>(a);
                                        Game* game = Game::getGame();
                                        State* s = game->getState();
                                        UI::Canvas* canvas = dynamic_cast<UI::Canvas*>(s->findObject("canvas"));
                                        std::cout << bt->getText();
                                        canvas->setColor(85*(std::stoi(bt->getText())+1),0,0);
                                        }}));
    }

    addObject(new UI::Button("brushUp",550,2,"","gfx/btBrushUp.png","gfx/btBrushUp.png",sf::Color::White,Action{
                                [](Object* a, Object* b, std::string arg1, std::string arg2){
                                    Game* game = Game::getGame();
                                    State* s = game->getState();
                                    UI::Canvas* canvas = dynamic_cast<UI::Canvas*>(s->findObject("canvas"));
                                    canvas->brushUp();
                                }
                             }));

    addObject(new UI::Button("brushDown",550,36,"","gfx/btBrushDown.png","gfx/btBrushDown.png",sf::Color::White,Action{
                                [](Object* a, Object* b, std::string arg1, std::string arg2){
                                    Game* game = Game::getGame();
                                    State* s = game->getState();
                                    UI::Canvas* canvas = dynamic_cast<UI::Canvas*>(s->findObject("canvas"));
                                    canvas->brushDown();
                                }
                             }));

    cssmgr->loadFromFile("css//text.css");
    UI::cssHandler* css = cssmgr->getCss("#test");
    std::cout << css << std::endl;
    css->print();
    /*
    addObject(new UI::Button("test", *css,"","","",
                                Action{[](Object* a, Object* b, std::string arg1, std::string arg2){
                                    std::cout << "ebebebe" << std::endl;
                                }
                            }));
    */
    //UI::cssHandler* css = new UI::cssHandler;
    //addObject(new UI::Input("inp", *css,"fonts/arial.ttf"));


}

void FirstState::cleanup()
{
    std::cout << "FirstState: cleanup" << std::endl;
}

void FirstState::handleEvents(sf::RenderWindow* window)
{
    //std::cout << "FirstState: events" << std::endl;
    if(!paused)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            Game* game = Game::getGame();
            game->popState();
            return;
        }
    }

    sf::Event event;
    while (window->pollEvent(event))
    {
        if(!paused)
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
                Game::getGame()->stop();
            }
            if (event.type == sf::Event::TextEntered)
            {
                if(focus!=nullptr && focus->isOfType("textInput"))
                    if (event.text.unicode < 128)
                        dynamic_cast<UI::Input*>(focus)->sendChar(static_cast<char>(event.text.unicode));

            }
            if(event.type == sf::Event::LostFocus) pause();
        }

        if(event.type == sf::Event::GainedFocus) resume();
    }
}

void FirstState::pause()
{
    std::cout << "FirstState: pause" << std::endl;
    paused = true;
}

void FirstState::resume()
{
    std::cout << "FirstState: resume" << std::endl;
    paused = false;
}

void FirstState::update()
{
    //std::cout << "FirstState: update" << std::endl;
    if(!paused)
    {
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
    }

}

void FirstState::render(sf::RenderWindow* window)
{
    //std::cout << "FirstState: render" << std::endl;
    for(auto el : objects)
    {
        //std::cout << el << std::endl;
        if(el!=nullptr) window->draw(*el);
    }
}
