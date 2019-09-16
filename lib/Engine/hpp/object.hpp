#ifndef OBJECT_H
#define OBJECT_H

#include "animation.hpp"
//#include "event.hpp"
#include "customTypes.hpp"

class Event;
class Object :public sf::Drawable
{
public:
    Object();
    ~Object();
    virtual void update() = 0;
    void factory(Object*, std::vector<Object*>*);
    void setObjsRef(std::vector<Object*>*);
    sf::IntRect* getHitbox();
    sf::Sprite* getSprite();
    virtual void collide(Object*) = 0;
    std::string getId();
    std::vector<std::string> getTypes();
    void addType(std::string);
    void removeType(std::string);
    bool isOfType(std::string);
    //void setId(std::string);
    Object& getParent();
    Object& setParent(Object*);
    std::vector<Object*> getChildren();
    void addChild(Object*);
    Object& removeChild(unsigned int index);
    bool isContainer();
    void setContainer(bool arg);
protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
    void updateTexture(sf::Sprite&);
    sf::Vector2f moveTo(int x, int y);
    sf::Texture* currentTexture;
    Animation* currentAnimation;
    std::vector<Object*>* objs; //What is this?
    std::vector<Animation*> animation;
    std::vector<Event*> events;
    sf::Sprite *sprite;
    sf::IntRect* hitbox;
    void addSprite();
    void addEvent(std::string pred, std::string act);
    void addEvent(std::string pred, Action act);
    void addEvent(Predicate pred, std::string act);
    void addEvent(Predicate pred, Action act);
    void addAnimation(std::string name);
    std::string id;
    std::vector<std::string> types;
    std::vector<Object*> children;
    Object* parent;
    bool container;
};

#endif // OBJECT_H
