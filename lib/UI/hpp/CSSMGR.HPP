#ifndef CSSMGR_HPP
#define CSSMGR_HPP

#include "cssHandler.hpp"
#include <map>

namespace UI
{
    class cssMgr
    {
    public:
        cssMgr();
        ~cssMgr();
        void loadFromFile(std::string filename);
        cssHandler* getCss(std::string);
    private:
        std::map<std::string, cssHandler*>* styles;
        void parseCss(std::string);
        void seekNames(std::string text, cssHandler* css);
    };
}

#endif
