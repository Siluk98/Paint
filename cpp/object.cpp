#include "../hpp/object.hpp"
#include <iostream>
#include "../hpp/event.hpp"
#include "../hpp/animation.hpp"

Object::Object(){
    sprite = nullptr;
    hitbox = nullptr;
};
Object::~Object(){
    delete hitbox;
    delete sprite;
};

void Object::updateTexture(sf::Sprite &arg)
{
    currentAnimation->animate();
    if(currentAnimation->texture != nullptr)
    {
        currentTexture = currentAnimation->texture;
        //std::cout << "CT " << currentTexture << std::endl;
        arg.setTexture(*currentTexture, true);

    }

}

void Object::factory(Object* arg, std::vector<Object*>* v)
{
    v->push_back(arg);
}

void Object::setObjsRef(std::vector<Object*>* arg)
{
    objs = arg;
}

sf::IntRect* Object::getHitbox()
{
    return hitbox;
}


sf::Vector2f Object::moveTo(int x, int y)
{
    sf::Vector2f delta;
    if(sprite != nullptr)
    {
        delta = sprite->getPosition();
        sprite->setPosition(x,y);
    }
    if(hitbox != nullptr)
    {
        hitbox->top = x;
        hitbox->left = y;
    }
    delta.x -= x;
    delta.y -= y;
    return delta;
}

sf::Sprite* Object::getSprite()
{
    return sprite;
}

void Object::addSprite()
{
    sprite = new sf::Sprite;
    updateTexture(*sprite);
}

void Object::addEvent(std::string pred, std::string act)
{
    events.push_back(new Event(eventMgr::getInstance()));
    events.back()->create(pred, act);
}

void Object::addEvent(Predicate pred, std::string act)
{
    events.push_back(new Event(eventMgr::getInstance()));
    events.back()->create(pred, act);
}

void Object::addEvent(std::string pred, Action act)
{
    events.push_back(new Event(eventMgr::getInstance()));
    events.back()->create(pred, act);
}

void Object::addEvent(Predicate pred, Action act)
{
    events.push_back(new Event(eventMgr::getInstance()));
    events.back()->create(pred, act);
}

void Object::addAnimation(std::string name)
{
    animation.push_back(new Animation(currentTexture));
    animation.back() -> loadTexture(name);
}
