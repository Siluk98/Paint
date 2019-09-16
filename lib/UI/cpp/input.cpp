#include "../hpp/input.hpp"
#include "../hpp/cssHandler.hpp"
#include "../../Engine/hpp/fontMgr.hpp"
#include <iostream>
#include "../../Engine/hpp/state.hpp"
#include "../../Engine/hpp/game.hpp"
#include "../../Engine/hpp/event.hpp"

UI::Input::Input(std::string id, cssHandler& css, std::string f="fonts/arial.ttf"){
    this->id = id;
    focus = false;
    caretVisible = true;
    addType("textInput");
    container = true;
    float posx=0;
    float posy=50;
    //focus = !focus;
    caretCounter = 0;
    caretMax = 60;
    field = new sf::RectangleShape(sf::Vector2f{128,32});
    field->setFillColor(sf::Color::White);
    field->setPosition(sf::Vector2f{posx,posy});
    caret = new sf::RectangleShape(sf::Vector2f{1,28});
    caret->setPosition(posx+1,posy+1);
    caretColor = new sf::Color(0,0,0,255);
    caret->setFillColor(*caretColor);
    hitbox = new sf::IntRect(posx+1,posy+1,128,32);
    text = new sf::Text;

    font = fontMgr::getInstance()->loadFont(f);

    text->setFont(*font);
    text->setCharacterSize(28);
    text->setFillColor(sf::Color::Black);
    text->setPosition(posx+1,posy);
    addEvent("MouseDown", Action{[](Object* a, Object* b, std::string arg1, std::string arg2){
                    UI::Input *c = dynamic_cast<UI::Input*>(a);
                    c->focus = true;
                    State* s = Game::getGame()->getState();
                    s->setFocus(c);
                    std::cout << "Focus" << std::endl;
             }});

    addEvent("MouseOut", Action{[](Object* a, Object* b, std::string arg1, std::string arg2){
                    UI::Input* c = dynamic_cast<UI::Input*>(a);
                    c->focus = false;
                    if(c->caretVisible) c->caretBlink();
                    std::cout << "Out of focus" << std::endl;
             }});
}
UI::Input::~Input(){
    delete text;
    delete field;
    delete caret;
    delete font; // dangling pointer
}

void UI::Input::update()
{
    for(unsigned int i=0;i<events.size();i++)
    {
        events[i]->handle(this,nullptr,"","");
    }
    //updateTexture(*sprite);
    if(focus)
    {
        caretCounter++;
        if(caretCounter>=caretMax)
        {
            caretCounter = 0;
            caretBlink();
        }
    }
}

void UI::Input::caretBlink()
{
    std::cout << "blink" << std::endl;
    if(caretVisible)
        caretColor->a = 0;
    else
        caretColor->a = 255;
    caret->setFillColor(*caretColor);
    caretVisible = !caretVisible;
}

void UI::Input::draw(sf::RenderTarget &target, sf::RenderStates s) const
{
    target.draw(*field);
    target.draw(*text);
    target.draw(*caret);
}


void UI::Input::changeStyle(std::string atr, std::string val)
{
    /*
    try
    {
        if(val == "") return;
        std::cout << id << ": " << atr << ": " << val << std::endl;
        int i = std::stoi(val);
        if(atr == "width")
        {
            auto s = sprite->getScale();
            auto bounds = sprite->getGlobalBounds();
            float ns = i/bounds.width;
            sprite->setScale(ns,s.y);
            delete hitbox;
            hitbox = new sf::IntRect(sprite->getGlobalBounds());
        }
        if(atr == "height")
        {
            auto s = sprite->getScale();
            auto bounds = sprite->getGlobalBounds();
            float ns = i/bounds.height;
            sprite->setScale(s.x,ns);
            delete hitbox;
            hitbox = new sf::IntRect(sprite->getGlobalBounds());
        }
        if(atr == "top")
        {
            std::cout << sprite->getPosition().x << " " << i << std::endl;
            moveTo(sprite->getPosition().x,i);
        }
        if(atr == "left")
        {
            std::cout << i << " " << sprite->getPosition().y << std::endl;
            moveTo(i,sprite->getPosition().y);
        }
        if(atr == "color")
        {

        }
    }
    catch(...)
    {
        std::cout << "Broken css" << std::endl;
    }
    */
}

std::string UI::Input::create(std::string obj, std::string params){return id;};

void UI::Input::sendChar(char c)
{
    if(c<=31){
        if(c==8 && !value.empty())
            value.pop_back();
    }
    else
        value.push_back(c);
    std::cout << "value: " << value << std::endl;
    updateText();
}

void UI::Input::updateText()
{
    text->setString(value);
}
