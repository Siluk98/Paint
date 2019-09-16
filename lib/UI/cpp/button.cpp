#include "../hpp/button.hpp"
#include <iostream>
#include "../../Engine/hpp/event.hpp"

using namespace UI;

Button::Button(){}

Button::Button(std::string id, int left, int top,std::string text, std::string active, std::string press,sf::Color color, Action act)
{
    std::cout << "btConst: " << id << std::endl;
    this->text = text;
    addAnimation(active);
    addAnimation(press);
    currentAnimation = animation[0];
    addSprite();
    sprite->setColor(color);
    hitbox = new sf::IntRect(0,0,sprite->getTexture()->getSize().x,sprite->getTexture()->getSize().y);
    moveTo(left,top);
    this->id = id;
    isPressed = false;
    click = act;
    container = true;
    addType("button");
    addEvent("MouseDown", Action{[](Object* a, Object* b, std::string arg1, std::string arg2){
                UI::Button *c = dynamic_cast<Button*>(a);
                c->isPressed = true;
                c->currentAnimation = c->animation[1];
                c->currentAnimation->animate();
             }});
    addEvent("MouseUp", Action{[](Object* a, Object* b, std::string arg1, std::string arg2){
                    Button *c = dynamic_cast<Button*>(a);
                    if(c->isPressed)
                    {
                        std::cout << "click " << c->id << std::endl;
                        c->isPressed = false;
                        c->currentAnimation = c->animation[0];
                        c->currentAnimation->animate();
                        if(c->click) c->click(c, nullptr, "", "");
                    }
             }});
    std::cout << "btConstEnd: " << id << std::endl;
}

Button::Button(std::string id, cssHandler& css,std::string text="",std::string active="bt.png", std::string press="bt.png", Action act = nullptr)
{
    this->id = id;
    addAnimation(active);
    addAnimation(press);
    currentAnimation = animation[0];
    addSprite();
    hitbox = new sf::IntRect(0,0,sprite->getTexture()->getSize().x,sprite->getTexture()->getSize().y);
    applyStyle(css);
    click = act;
    container = true;
    addType("button");
    addEvent("MouseDown", Action{[](Object* a, Object* b, std::string arg1, std::string arg2){
                UI::Button *c = dynamic_cast<Button*>(a);
                c->isPressed = true;
                c->currentAnimation = c->animation[1];
                c->currentAnimation->animate();
             }});
    addEvent("MouseUp", Action{[](Object* a, Object* b, std::string arg1, std::string arg2){
                    Button *c = dynamic_cast<Button*>(a);
                    if(c->isPressed)
                    {
                        std::cout << "click " << c->id << std::endl;
                        c->isPressed = false;
                        c->currentAnimation = c->animation[0];
                        c->currentAnimation->animate();
                        if(c->click) c->click(c, nullptr, "", "");
                    }
             }});
}

Button::~Button(){};

void Button::update()
{
    for(unsigned int i=0;i<events.size();i++)
    {
        events[i]->handle(this,nullptr,"","");
    }
    updateTexture(*sprite);
}

void Button::collide(Object* collider){}
std::string Button::create(std::string obj, std::string params){return this->id;}
void Button::draw(sf::RenderTarget &target, sf::RenderStates s) const
{

    target.draw(*sprite);
}

std::string Button::getText(){return text;}

void Button::changeStyle(std::string atr, std::string val)
{
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
}
