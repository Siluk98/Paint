#ifndef STATE_HPP
#define STATE_HPP

#include <vector>
#include "object.hpp"
#include "eventMgr.hpp"
#include "AUDIOMGR.HPP"

class State
{
public:
    State(gfxMgr*, eventMgr*);
    State();
    void setMgrs(gfxMgr*, eventMgr*, audioMgr*);
    virtual ~State()=0;
    void addObject(Object*);
    void removeObject(std::string id);
    Object* findObject(std::string id);
    int findObjectIndex(std::string id);
    virtual void init()=0;
    virtual void cleanup()=0;
    virtual void handleEvents(sf::RenderWindow*)=0;
    virtual void update()=0;
    virtual void render(sf::RenderWindow*)=0;
    virtual void pause()=0;
    virtual void resume()=0;
    std::string getId();
    void setFocus(Object*);
    bool isPaused();
protected:
    std::vector<Object*> objects;
    std::string id;
    bool paused;
    Object* focus;
    gfxMgr* gfxmgr;
    eventMgr* eventmgr;
    audioMgr* audiomgr;
};

#endif // STATE_HPP
