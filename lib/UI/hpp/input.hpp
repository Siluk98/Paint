#ifndef UI_INPUT_HPP
#define UI_INPUT_HPP

#include "ui.hpp"

namespace UI
{
    class Input :public Component
    {
    public:
        Input(std::string id, cssHandler& css, std::string font);
        ~Input();
        std::string getText();
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void update();
        void collide(Object*){};
        void changeStyle(std::string atr,std::string val);
        std::string create(std::string obj, std::string params);
        void sendChar(char c);
    private:
        int caretCounter;
        int caretMax;
        bool caretVisible;
        sf::Color* caretColor;
        std::string id;
        sf::RectangleShape* field;
        sf::RectangleShape* caret;
        sf::Text* text;
        sf::Font* font;
        bool focus;
        std::string value;
        void caretBlink();
        void updateText();
    };
}

#endif
