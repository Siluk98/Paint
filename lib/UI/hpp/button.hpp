#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "ui.hpp"
#include "../../../hpp/customTypes.hpp"

namespace UI
{
    class Button : virtual public UI::Component
    {
    public:
        Button();
        Button(std::string id, int left, int top, std::string text, std::string active, std::string press,sf::Color color, Action act);
        ~Button();
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void update();
        void collide(Object*);
        std::string create(std::string obj, std::string params);
        std::string getText();
    private:
        std::string text;
        bool isPressed;
        sf::Sprite* press;
        sf::Sprite* active;
        Action click;
    };
}


#endif
