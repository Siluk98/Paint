#include "../hpp/cssHandler.hpp"

#include <fstream>
#include <iostream>

using namespace UI;

cssHandler::cssHandler()
{

}

cssHandler::~cssHandler()
{

}

/*
void cssHandler::loadFromFile(std::string filename)
{
    std::fstream f;
    f.open(filename.c_str(),std::ios::in);
    if(f.good())
    {
        std::string name;
        std::string atr;
        while(!f.eof())
        {
            std::getline(f,name,':');
            std::getline(f,atr);
            while(name.back()==' ') name.pop_back();
            while(name.front()==' ') name.erase(0,1);
            while(atr.back()==' ' || atr.back()==';') atr.pop_back();
            while(atr.front()==' ') atr.erase(0,1);
            changeAttribute(name, atr);
        }
    }
}
*/

void cssHandler::changeAttribute(std::string atr, std::string val)
{
    style[atr] = val;
}

std::string cssHandler::getAttribute(std::string atr)
{
    return style[atr];
}

std::map<std::string, std::string>& cssHandler::getStyle()
{
    return style;
}

void cssHandler::print()
{
    for(auto i: style)
    {
        std::cout << i.first << ":" << i.second << std::endl;
    }
}
