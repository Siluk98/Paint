#include "../hpp/enemyBullet.hpp"

#include <iostream>

int EnemyBullet::counter = 0;

EnemyBullet::EnemyBullet(sf::Vector2f pos, std::vector<Object*>* ptr)
{
    counter++;
    std::cout << "E Bullet Construction" << counter << std::endl;
    animation.push_back(new Animation(currentTexture));
    animation[0] -> setDif(5);
    animation[0] -> loadTexture("gfx/ebullet1.png");
    animation[0] -> loadTexture("gfx/ebullet2.png");
    currentAnimation = animation[0];
    sprite = new sf::Sprite;
    sprite -> setPosition(pos.x,pos.y);
    objs = ptr;
    std::cout << "E Bullet Loading c" << counter << std::endl;
    speed = 5;

    updateTexture(*sprite);
    std::cout << "E Bullet Done" << counter << std::endl;
};



EnemyBullet::~EnemyBullet()
{
    std::cout << "E Bullet Destruction: ";
    counter--;
    for(auto it = objs->begin();it!=objs->end();it++)
    {
        //std::cout << *it << std::endl;
        if(*it == this)
        {
            objs->erase(it);
            break;
        }
    }
    std::cout << "Done" << std::endl;
    //delete sprite;
    /*
    for(auto el:animation)
    {
        delete el;
    }
    */
}

void EnemyBullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //currentAnimation->animate();
    target.draw(*sprite);
}

void EnemyBullet::update()
{
    sprite->move(0, speed);
    if(sprite->getPosition().y > 1000)
    {
        delete this;
    }

    if(currentAnimation == nullptr) std::cout << "E Bullet Animation null" << std::endl;
    if(currentTexture == nullptr) std::cout << "E Bullet Texture null" << std::endl;
    updateTexture(*sprite);

}

void EnemyBullet::collide(Object* collider)
{

}
