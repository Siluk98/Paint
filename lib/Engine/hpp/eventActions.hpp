#ifndef ACTIONS_HPP
#define ACTIONS_HPP
#include "event.hpp"
#include "eventMgr.hpp"

#include <iostream>

inline void initDefaultActions(eventMgr *mgr)
{
    mgr->addAction("action", Action {[](Object* a,Object* b,std::string arg1, std::string arg2){std::cout << "It works!";}});
    mgr->addAction("consoleLog", Action {[](Object* a,Object* b,std::string arg1, std::string arg2){std::cout << "Debug: " << arg1 << std::endl;}});
    //mgr->printActions();
}

#endif // ACTIONS_HPP
