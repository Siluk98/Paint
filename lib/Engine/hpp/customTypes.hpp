#ifndef TYPES_HPP
#define TYPES_HPP

#include <type_traits>
//using Predicate = bool(*)(Object*,Object*, std::string, std::string);
//using Action = void(*)(Object*,Object*, std::string, std::string);
class Object;
using Predicate = std::add_pointer<bool(Object*, Object*,std::string, std::string)>::type;
using Action = std::add_pointer<void(Object*, Object*,std::string, std::string)>::type;

#endif
