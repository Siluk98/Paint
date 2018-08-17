#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <string>
#include "gfxMgr.hpp"

class Animation
{
public:
    Animation();
    Animation(sf::Texture*);
    ~Animation();
    void animate();
    void loadTexture(std::string);
    sf::Texture* texture;
    void setDif(int);
private:
    std::vector<sf::Texture*> textureSet;
    sf::Texture* parentTexture;
    unsigned int current;
    int difMax;
    int dif;
};

#endif // ANIMATION_H
