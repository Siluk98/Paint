#include "../hpp/animation.hpp"
#include "../hpp/gfxMgr.hpp"

#include <iostream>

Animation::Animation(){
    parentTexture = nullptr;
    texture = nullptr;
    current = 0;
    dif = 0;
    difMax = 0;
};

Animation::Animation(sf::Texture* field){
    parentTexture = field;
    texture = nullptr;
    current = 0;
    dif = 0;
    difMax = 0;
};

Animation::~Animation(){
    std::cout << "Animation Destruction" << std::endl;
    //for(unsigned int i = 0;i<textureSet.size();i++)
        //delete textureSet[i];
    //delete parentTexture;
};


void Animation::animate()
{
    dif++;
    if(dif >= difMax)
    {
        dif = 0;
        current++;
        if(current>=textureSet.size())
        {
            current=0;
        }
        texture = textureSet[current];
        //std::cout << "TEST " << texture << std::endl;
        //parentTexture = texture;
    }
};

void Animation::loadTexture(std::string name)
{
    textureSet.push_back( gfxMgr::loadTexture(name));
}

void Animation::setDif(int arg)
{
    difMax = arg;
}
