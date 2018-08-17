#ifndef TESTOBJ_H
#define TESTOBJ_H

#include <SFML/Graphics.hpp>
#include "object.hpp"

class testObj : public Object
{
public:
    testObj(float arg, sf::Color col){
        shape = new sf::CircleShape(50);
        shape -> setFillColor(col);
        shape -> setPosition(arg,arg);
        r = 255;
        g = 0;
        b = 0;
        hitbox = new sf::IntRect(arg,arg,12,12);
    };
    ~testObj(){
        delete shape;
    };
private:
    sf::CircleShape* shape;
    int r,g,b;

    void update()
    {
        r--;
        g++;
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {

        shape -> setFillColor(sf::Color(r,g,b));
        target.draw(*shape);
    }

    void collide(Object*){b = 255;};
};

#endif // TESTOBJ_H
