#ifndef UI_HPP
#define UI_HPP


#include "cssHandler.hpp"
#include "../../Engine/hpp/object.hpp" //Rebuild engine to lib
#include "../../Engine/hpp/Functor.hpp"
#include <functional>

namespace UI
{
    class Component :public Object
    {
    public:
        virtual void update() = 0;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
        virtual void collide(Object*) = 0;
        virtual ~Component(){};
        virtual std::string create(std::string obj, std::string params) = 0;
        virtual void changeStyle(std::string atr, std::string val) = 0;
        void applyStyle(cssHandler& css);
        //std::map<std::string, std::function<void(void*,Component* pthis)>> functions;
        std::map<std::string, Functor*> functions;
        //void execute(std::string name, void* arg);
        void execute(std::string name);
        //void bind(std::string id, std::function<void(void*, Component* pthis)> fun);
        void bind(std::string id, Functor* fun);
    private:
    };
}

#include "button.hpp"
#include "canvas.hpp"

#endif
