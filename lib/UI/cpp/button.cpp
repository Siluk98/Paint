#include "../hpp/button.hpp"
#include <iostream>
#include "../../../hpp/event.hpp"

using namespace UI;

Button::Button(){}

Button::Button(std::string id, int left, int top, std::string active, std::string press)
{
    std::cout << "btConst: " << id << std::endl;
    addAnimation(active);
    addAnimation(press);
    currentAnimation = animation[0];
    addSprite();
    hitbox = new sf::IntRect(0,0,sprite->getTexture()->getSize().x,sprite->getTexture()->getSize().y);
    moveTo(left,top);
    std::cout << "test" << std::endl;
    this->id = id;
    isPressed = false;
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
                    }
             }});
    std::cout << "btConstEnd: " << id << std::endl;
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
