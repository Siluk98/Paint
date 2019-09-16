#ifndef UI_CHECKBOX_HPP
#define UI_CHECKBOX_HPP

#include "ui.hpp"

namespace UI
{
    class Checkbox :public Component
    {
    public:
        Checkbox(std::string id, cssHandler& css);
        Checkbox(std::string id, cssHandler* css);
        ~Checkbox();
        bool getValue();
        bool setValue(bool val);
        bool flipValue();
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void update();
        void collide(Object*){};
        void changeStyle(std::string atr,std::string val);
        std::string create(std::string obj, std::string params);
        sf::Vector2f moveTo(int x, int y);
    private:
        sf::Color outerColor;
        sf::Color innerColor;
        std::string id;
        sf::RectangleShape* outer;
        sf::RectangleShape* inner;
        bool value;
        bool isPressed;
        int innerWidth;
        int innerHeight;
        int outerWidth;
        int outerHeight;
    };
}

#endif
