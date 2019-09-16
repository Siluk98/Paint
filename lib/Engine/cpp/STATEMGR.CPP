#include "../hpp/stateMgr.hpp"

stateMgr::stateMgr()
{
    currentState = nullptr;
}

stateMgr::~stateMgr()
{
    for(auto e: states) delete e;
    currentState = nullptr;
}

/*
void stateMgr::addState(State* s)
{
    if(findState(s->getId())!=nullptr)
    {
        states.push_back(s);
    }
}

void stateMgr::removeState(std::string arg)
{
    int i=findStateIndex(arg);
    //Memory::deallocate(sizeof(states[i]));
    if(i!=-1)
        states.erase(states.begin()+i);
}
*/

void stateMgr::pushState(State* s)
{
    states.push_back(s);
    if(currentState!=nullptr)
    currentState->pause();
    s->init();
    currentState = s;
}

void stateMgr::popState()
{
    if(!states.empty())
    {
        //states.back()->cleanup();
        delete states.back();
        states.pop_back();
        if(!states.empty())
        {
            currentState = states.back();
            currentState->resume();
        }
        else currentState = nullptr;
    }
}

State* stateMgr::findState(std::string arg)
{
    for(auto i:states)
        if(i->getId() == arg)
            return i;
    return nullptr;
}

int stateMgr::findStateIndex(std::string arg)
{
    for(unsigned int it=0;it<states.size();it++)
        if(states[it]->getId() == arg)
            return it;
    return -1;
}

State* stateMgr::getState()
{
    return currentState;
}

unsigned int stateMgr::getSize()
{
    return states.size();
}
