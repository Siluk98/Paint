#ifndef RETFUNCTOR_HPP
#define RETFUNCTOR_HPP

#include <functional>
#include "object.hpp"

template<typename RV>
class RetFunctor
{
public:
    RetFunctor(unsigned int argno, std::function<void(void*,Object*,RV*)> func, bool takelv=false)
        :takeLV(takelv), argc(argno), fun(func){
            arg = nullptr;
            retval = new RV;
        };
    ~RetFunctor()
    {
        //delete retval;
    }
    RV operator() (void* args, Object* pthis=nullptr){
        if(fun) fun(arg,pthis, retval);
        return *retval;
    }
    getArgc(){return argc;};
protected:
    bool takeLV;
    unsigned int argc;
    void* arg;
    RV* retval;
    std::function<void(void*,Object*,RV*)> fun;
private:
};



#endif

