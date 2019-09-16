#include "../hpp/eventMgr.hpp"
#include <iostream>
#include "../hpp/eventActions.hpp"
#include "../hpp/eventPredicates.hpp"

eventMgr* eventMgr::instance = nullptr;

eventMgr::eventMgr(){
    objectActions = new std::map<std::string, Action>;
    objectPredicates = new std::map<std::string, Predicate>;
    instance = this;
    initDefaultActions(this);
    initDefaultPredicates(this);
    std::cout << "EventMgr Const" << std::endl;
};

eventMgr::~eventMgr(){
    instance = nullptr;
    std::cout << "EventMgr Deleted" << std::endl;
};

eventMgr* eventMgr::create()
{
    if(instance != nullptr) return instance;
    return new eventMgr;
}

Predicate eventMgr::addPredicate(std::string name, Predicate pred)
{
    (*objectPredicates)[name] = pred;
    return (*objectPredicates)[name];
    //return nullptr;
}

Action eventMgr::addAction(std::string name, Action act)
{
    (*objectActions)[name] = act;
    return (*objectActions)[name];
    //return nullptr;
}

Predicate eventMgr::getPredicate(std::string name)
{
    if(objectPredicates->find(name) == objectPredicates->end())
    {
        return nullptr;
    }
    else
    {
        return (*objectPredicates)[name];
    }
}

Action eventMgr::getAction(std::string name)
{
    if(objectActions->find(name) == objectActions->end())
    {
        return nullptr;
    }
    else
    {
        return (*objectActions)[name];
    }
}

eventMgr* eventMgr::getInstance()
{
    return instance;
}

void eventMgr::printPredicates()
{
    for (auto it = objectPredicates->begin(); it != objectPredicates->end(); it++ )
    {
        std::cout << it->first << std::endl ;
    }
}

void eventMgr::printActions()
{
    for (auto it = objectActions->begin(); it != objectActions->end(); it++ )
    {
        std::cout << it->first << std::endl ;
    }
}
