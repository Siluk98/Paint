#ifndef FONTMGR_HPP
#define FONTMGR_HPP

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class fontMgr
{
public:
    ~fontMgr();
    sf::Font* loadFont(std::string name);
    static fontMgr* getInstance();
    static fontMgr* create();
private:
    fontMgr();
    std::vector<sf::Font*> fonts;
    static fontMgr* instance;
};

#endif
