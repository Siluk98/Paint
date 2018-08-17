#include "../hpp/playerController.hpp"

PlayerController::PlayerController(){};
PlayerController::~PlayerController(){};

void PlayerController::changeControls(sf::Keyboard::Key key, std::function<void(void)> func)
{
    bool flag = true;
    for(auto i = controls.begin();i!=controls.end();i++)
    {
        if(i->first == key)
        {
            i->second = func;
            flag = false;
            break;
        }
    }
    if(flag)
    {
        controls.push_back(std::pair<sf::Keyboard::Key,std::function<void(void)>>(key,func));
    }
}

void PlayerController::iterate()
{
    for(auto i = controls.begin();i!=controls.end();i++)
    {
        if(sf::Keyboard::isKeyPressed(i->first))
        {
            i->second();
        }
    }
}
