#ifndef UI_CANVAS_HPP
#define UI_CANVAS_HPP

#include "ui.hpp"
#include "../../Engine/hpp/customTypes.hpp"

namespace UI
{
    class Canvas : virtual public UI::Component
    {
    public:
        Canvas();
        Canvas(std::string id, int left, int top, unsigned int width, unsigned int height);
        ~Canvas();
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void update();
        void collide(Object*);
        void changeStyle(std::string atr,std::string val);
        std::string create(std::string obj, std::string params);
        void clear();
        void save(std::string name);
        void load(std::string name);
        void setColor(char, char, char);
        void brushUp();
        void brushDown();
    private:
        void drawCircle(int x,int y, int r);
        void drawDiamond(int x,int y, int r);
        void drawPixel(unsigned int x,unsigned int y);
        void floodfill(int x, int y);
        static sf::Color paint;
        static unsigned int brushSize;
        static unsigned int brushMax;
        sf::Image* drawspace;
        sf::Texture* texture;
        unsigned int width;
        unsigned int height;
    };
}

#endif
