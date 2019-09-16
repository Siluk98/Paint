#ifndef EVENTMGR_HPP
#define EVENTMGR_HPP

#include <functional>
#include <map>
//include "event.hpp"
#include "object.hpp"

//using Predicate = bool(*)(Object*,Object*, std::string, std::string);
//using Action = void(*)(Object*,Object*, std::string, std::string);
#include "customTypes.hpp"

class Event;
//change to singleton
class eventMgr
{
public:

    ~eventMgr();
    Predicate addPredicate(std::string, Predicate);
    Action addAction(std::string, Action);
    Predicate getPredicate(std::string);
    Action getAction(std::string);
    static eventMgr* getInstance();
    static eventMgr* create();
    void printPredicates();
    void printActions();
private:
    eventMgr();
    std::vector<Event*> events;
    std::map<std::string, Predicate>* objectPredicates;
    std::map<std::string, Action>* objectActions;
    //static std::map<std::string, std::function<bool(Object*,Object*,std::string)>> objectPredicates;
    static eventMgr* instance;
};

#endif // EVENTMGR_HPP
