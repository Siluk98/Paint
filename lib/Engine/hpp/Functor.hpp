#ifndef FUNCTOR_HPP
#define FUNCTOR_HPP

#include <functional>
#include "object.hpp"

class Functor
{
public:
    Functor(void* args, std::function<void(void*,Object*)> func)
        :arg(args), fun(func){};
    ~Functor();
    void operator() (Object* pthis){
        if(fun) fun(arg,pthis);
    }
protected:
    void* arg;
    std::function<void(void*,Object*)> fun;
private:
};



#endif
