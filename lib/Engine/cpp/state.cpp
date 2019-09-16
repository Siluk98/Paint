#include "../hpp/state.hpp"

/*
State::State(gfxMgr* g, eventMgr* e)
:gfxmgr{g}, eventmgr{e}
{
    //Memory::allocate(sizeof(this));
}
*/

State::State()
{
    focus = nullptr;
    paused = false;
}

State::~State()
{

}

Object* State::findObject(std::string id)
{
    for(Object* e:objects)
    {
        if(e->getId() == id) return e;
    }
    return nullptr;
}

int State::findObjectIndex(std::string id)
{
    int i=0;
    for(Object* e:objects)
    {
        i++;
        if(e->getId() == id) return i;
    }
    return -1;
}

void State::addObject(Object* obj)
{
    if(findObject(obj->getId())==nullptr)
    {
        objects.push_back(obj);
        //Memory::allocate(sizeof(*obj));
        //Memory::print();
    }
}

void State::removeObject(std::string id)
{
    if(int i=findObjectIndex(id)!=-1)
    {
        //Memory::deallocate(sizeof(*objects[i]));
        delete objects[i];
        objects.erase(objects.begin()+i);
        //Memory::print();
    }
}

std::string State::getId()
{
    return id;
}

void State::setMgrs(gfxMgr* g, eventMgr* e, audioMgr* a)
{
    gfxmgr = g;
    eventmgr = e;
    audiomgr = a;
}

void State::setFocus(Object* obj)
{
    focus = obj;
}

bool State::isPaused()
{
    return paused;
}
