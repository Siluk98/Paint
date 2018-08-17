#ifndef BG_H
#define BG_H

#include "object.hpp"
#include <SFML/Graphics.hpp>

class Background : public Object
{
    public:
        Background(int,int,bool);
        ~Background();
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void collide(Object*);
        void update();
        float getPositiony();
        float getPositionx();
        void setPositiony(float);
        void setPositionx(float);
        float getSizey();
        float getSizex();
    private:
        bool t;
        //sf::Sprite *sprite;
};

#endif // BG_H
