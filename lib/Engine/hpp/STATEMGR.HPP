#ifndef STATEMGR_HPP
#define STATEMGR_HPP
#include "state.hpp"
#include <string>
#include <vector>

class stateMgr
{
public:
    stateMgr();
    ~stateMgr();
    //void addState(State*);
    //void removeState(std::string id);
    void popState();
    void pushState(State* s);
    unsigned int getSize();
    State* findState(std::string id);
    int findStateIndex(std::string id);
    State* getState();
private:
    std::vector<State*> states;
    State* currentState;
};

#endif
