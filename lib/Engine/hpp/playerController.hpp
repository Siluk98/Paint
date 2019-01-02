#ifndef PLAYER_CONTORLLER
#define PLAYER_CONTORLLER

#include <SFML/Window/Keyboard.hpp>
#include <functional>
//#include <map>
#include <vector>

class PlayerController
{
public:
    PlayerController();
    ~PlayerController();
    //void changeControls(Direction&,sf::Keyboard::Key);
    void changeControls(sf::Keyboard::Key, std::function<void(void)>);
    void iterate();
private:
    std::vector<std::pair<sf::Keyboard::Key, std::function<void(void)>>> controls;
    //controlModel controls;
};

#endif // PLAYER_CONTORLLER
