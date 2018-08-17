#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "ui.hpp"

namespace UI
{
    class Button : virtual public UI::Component
    {
    public:
        Button();
        Button(std::string id, int left, int top, std::string active, std::string press);
        ~Button();
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void update();
        void collide(Object*);
        std::string create(std::string obj, std::string params);
    private:
        sf::Text text;
        bool isPressed;
        sf::Sprite* press;
        sf::Sprite* active;
        std::string id;
    };
}


#endif
