#ifndef UI_HPP
#define UI_HPP

#include "style.hpp"
#include "cssHandler.hpp"
#include "../../Engine/hpp/object.hpp" //Rebuild engine to lib
#include <functional>

namespace UI
{
    class Component :public Object
    {
    public:
        virtual void update() = 0;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
        virtual void collide(Object*) = 0;
        ~Component(){};
        virtual std::string create(std::string obj, std::string params) = 0;
        virtual void changeStyle(std::string atr, std::string val) = 0;
        void applyStyle(cssHandler& css);
        //virtual void bind(std::string id, std::function fun);
        //bind(std::string name, &T); // ?
    private:
    };
}

#include "range.hpp"
#include "button.hpp"
#include "canvas.hpp"

#endif
