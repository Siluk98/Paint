#ifndef EVENT_HPP
#define EVENT_HPP

#include <functional>
#include "object.hpp"
#include "eventMgr.hpp"

//using Predicate = std::function<bool(Object*,Object*, std::string)>;
//using Action = std::function<void(Object*,Object*, std::string)>;



class Event
{
public:
    Event(eventMgr *mgr);
    ~Event();
    void execute(Object*,Object*, std::string, std::string);
    bool check(Object*,Object*, std::string, std::string);
    void handle(Object*,Object*, std::string, std::string);
    void create(std::string,std::string);
    void create(Predicate,std::string);
    void create(std::string,Action);
    void create(Predicate,Action);
private:
    std::string predName;
    std::string actionName;
    Predicate predicate;
    Action action;
    eventMgr* eventmgr;
};

#endif // EVENT_HPP
