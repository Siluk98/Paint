#include "../hpp/object.hpp"
#include <iostream>
#include "../hpp/event.hpp"
#include "../hpp/animation.hpp"
#include "../hpp/errorCalls.hpp"

Object::Object(){
    sprite = nullptr;
    hitbox = nullptr;
    types.push_back("object");
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
        hitbox->top = y;
        hitbox->left = x;
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

std::string Object::getId(){return id;}
std::vector<std::string> Object::getTypes(){return types;}

void Object::addType(std::string s){
    auto it = std::find(types.begin(), types.end(),s);
    if(it == types.end())
    {
        types.push_back(s);
    }
};

void Object::removeType(std::string s){
    auto it = std::find(types.begin(), types.end(),s);
    if(it != types.end())
    {
        types.erase(it);
    }
};

bool Object::isOfType(std::string s)
{
    auto it = std::find(types.begin(), types.end(),s);
    return (it != types.end());
}

std::vector<Object*> Object::getChildren(){return children;};

void Object::addChild(Object* arg)
{
    auto it = std::find(children.begin(), children.end(),arg);
    if(it != children.end())
    {
        children.push_back(arg);
    }
}

Object& Object::removeChild(unsigned int index)
{
    if(index>children.size()-1 || index<0)
    {
        std::cout << "Domain error";
        callDomainError(index, children.size(),__FILE__,__LINE__);
    }
    Object& ret = *(children[index]);
    children.erase(children.begin()+index);
    return ret;
}

Object& Object::getParent()
{
    return *parent;
}

Object& Object::setParent(Object* arg)
{
    parent = arg;
    return *arg;
}

bool Object::isContainer()
{
    return container;
}

void Object::setContainer(bool arg)
{
    container = arg;
}
