#include "../hpp/background.hpp"

#include <typeinfo>
#include <iostream>
#include <random>
#include "../hpp/event.hpp"
//#include "../hpp/eventMgr.hpp"

Background::Background(int x, int y, bool _t)
{
    std::cout << "Background Construction" << std::endl;
    animation.push_back(new Animation(currentTexture));
    animation[0] -> loadTexture("gfx/bg.png");
    currentAnimation = animation[0];
    sprite = new sf::Sprite;
    updateTexture(*sprite);
    //sprite -> setPosition(0.0f,0.0f);
    hitbox = new sf::IntRect(0,0,sprite->getTexture()->getSize().x,sprite->getTexture()->getSize().y);
    moveTo(x,y);
    t = _t;
    events.push_back(new Event(eventMgr::getInstance()));
    //events.back()->create("pred","action");
    events.back()->create("click","consoleLog");
};


Background::~Background(){}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //currentAnimation->animate();
    target.draw(*sprite);
}

void Background::update()
{
    /*for(auto i: events)
    {
        i->execute(nullptr,nullptr, "","");
    }*/

    events.back()->handle(this,nullptr,"Click","");

    if(currentAnimation == nullptr) std::cout << "Animation null" << std::endl;
    if(currentTexture == nullptr) std::cout << "Texture null" << std::endl;
    updateTexture(*sprite);
    //moveTo(sprite->getPosition().x-1+2*t, sprite->getPosition().y);
    /*sprite -> setPosition(sprite->getPosition().x, sprite->getPosition().y-1);
    //std::cout << "bbbb " << (0-(int)sprite->getTexture()->getSize().y) << std::endl;
    //std::cout << "aaaa " << sprite->getPosition().y << std::endl;
    if(sprite->getPosition().y < (0 - (int)sprite->getTexture()->getSize().y))
    {
        //setPositiony(torus->getPositiony()+torus->getSizey());
    }*/
}

void Background::collide(Object* obj)
{
    t = !t;
    std::cout << "bg Collision: " << obj << ": " << typeid(*obj).name() << std::endl;
}

float Background::getPositiony()
{
    return sprite->getPosition().y;
}

float Background::getPositionx()
{
    return sprite->getPosition().x;
}

void Background::setPositiony(float arg)
{
    sprite->setPosition(sprite->getPosition().x, arg);
}

void Background::setPositionx(float arg)
{
    sprite->setPosition(arg, sprite->getPosition().y);
}

float Background::getSizey()
{
    return (int)sprite->getTexture()->getSize().y;
}

float Background::getSizex()
{
    return (int)sprite->getTexture()->getSize().x;
}
