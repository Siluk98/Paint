#ifndef EBULLET_H
#define EBULLET_H

#include "object.hpp"

class EnemyBullet : public Object
{
public:
    EnemyBullet(sf::Vector2f, std::vector<Object*>*);
    ~EnemyBullet();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void update();
    void collide(Object* collider);
private:
    sf::Sprite *sprite;
    float speed;
    static int counter;
};

#endif // BULLET_H
