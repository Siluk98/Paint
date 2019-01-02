#include "../hpp/ui.hpp"

using namespace UI;

void Component::applyStyle(cssHandler& css)
{
    for(auto i = css.getStyle().begin();i!=css.getStyle().end();i++)
    {
        changeStyle(i->first,i->second);
    }
}
