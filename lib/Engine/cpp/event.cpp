#include "../hpp/event.hpp"
#include <iostream>
#include "../hpp/eventMgr.hpp"

Event::Event(eventMgr* mgr){
    predicate = nullptr;
    action = nullptr;
    predName = "Anonymous";
    actionName = "Anonymous";
    eventmgr = mgr;
};
Event::~Event(){};

void Event::execute(Object* arg1 = nullptr,Object*arg2 = nullptr, std::string arg3= "",std::string arg4= ""){
    if(action != nullptr)
    {
        action(arg1,arg2,arg3,arg4);
    }
    else
    {
        std::cout << "Action " << actionName << " is not defined";
    }
};
bool Event::check(Object* arg1 = nullptr,Object*arg2 = nullptr, std::string arg3= "",std::string arg4= ""){
    if(predicate != nullptr)
    {
        return predicate(arg1,arg2,arg3,arg4);
    }
    else
    {
        std::cout << "Predicate " << predName << " is not defined";
        return false;
    }
};
void Event::handle(Object* arg1 = nullptr,Object*arg2 = nullptr, std::string arg3= "",std::string arg4= ""){
    if(check(arg1,arg2,arg3,arg4))
    {
        execute(arg1,arg2,arg3,arg4);
    }
};
void Event::create(std::string pred, std::string act){
    predName = pred;
    actionName = act;
    predicate = eventmgr->getPredicate(pred);
    action = eventmgr->getAction(act);
};
void Event::create(Predicate pred, std::string act){
    predicate = pred;
    actionName = act;
    action = eventmgr->getAction(act);
};
void Event::create(std::string pred, Action act){
    if(eventmgr)
   predName = pred;
   predicate = eventmgr->getPredicate(pred);
   action = act;
};
void Event::create(Predicate pred, Action act){
    predicate = pred;
    action = act;
};
