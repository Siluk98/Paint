#include "../hpp/eventMgr.hpp"

eventMgr* eventMgr::instance = nullptr;

eventMgr::eventMgr(){
    objectActions = new std::map<std::string, Action>;
    objectPredicates = new std::map<std::string, Predicate>;
    instance = this;
};
eventMgr::~eventMgr(){};

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
