#ifndef UI_CSSHANDLER_HPP
#define UI_CSSHANDLER_HPP

#include <string>
#include <map>

namespace UI
{
    //class Component;
    class cssHandler
    {
    public:
        cssHandler();
        ~cssHandler();
        //void loadFromFile(std::string filename);
        void changeAttribute(std::string atr, std::string val);
        std::string getAttribute(std::string atr);
        std::map<std::string,std::string>& getStyle();
        void print();
    private:
        std::map<std::string, std::string> style;
    };
}

#endif // UI_CSSHANDLER_HPP

