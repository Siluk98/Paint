#include "../hpp/gfxmgr.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

gfxMgr::gfxMgr(){};
gfxMgr::~gfxMgr(){};

std::map<std::string,sf::Texture> gfxMgr::textures;

sf::Texture* gfxMgr::loadTexture(std::string name)
{
    if(textures.find(name) == textures.end())
    {
        sf::Texture * t = new sf::Texture;
        if(!t->loadFromFile(name))
        {
            std::cout << "Texture " << name << " failed to load" << std::endl;
            delete t;
            t = gfxMgr::loadTexture("gfx/placeholder.png");
        }
        gfxMgr::textures[name] = *t;
        return &gfxMgr::textures[name];
    }
    else
    {
        return &textures[name];
    }

}

int gfxMgr::getMapSize()
{
    return gfxMgr::textures.size();
}


