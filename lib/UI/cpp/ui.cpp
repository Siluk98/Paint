#include "../hpp/ui.hpp"

//using namespace UI;

void UI::Component::applyStyle(cssHandler& css)
{
    for(auto i = css.getStyle().begin();i!=css.getStyle().end();i++)
    {
        changeStyle(i->first,i->second);
    }
}

/*
void UI::Component::execute(std::string name, void* arg)
{
    if(functions.find(name)!=functions.end() && functions[name] != nullptr)
        functions[name](arg, this);
}
*/
/*
void UI::Component::bind(std::string id,
                         std::function<void(void* arg,UI::Component* pthis)> func)
{
    functions[id] = func;
}
*/

void UI::Component::execute(std::string name)
{
    if(functions.find(name)!=functions.end() && functions[name] != nullptr)
        (*(functions[name]))(this);
}

void UI::Component::bind(std::string id, Functor* func)
{
    functions[id] = func;
}
