#include "../hpp/CSSMGR.HPP"
#include <fstream>
#include <regex>
#include <iostream>

using namespace UI;

cssMgr::cssMgr(){
    styles = new std::map<std::string, cssHandler*>;
    std::cout << "Cstyles: " << styles << std::endl;
};
cssMgr::~cssMgr(){
    /*
    for(auto i = styles.begin();i!=styles.end();i++)
    {
        delete i->second;
    }
    styles.empty();
    */
};

void cssMgr::loadFromFile(std::string filename)
{
    std::ifstream file;
    file.open(filename);
    if(file.good())
    {
        std::string text{};

        while(!file.eof())
        {
            std::string line; // optimize
            std::getline(file,line);
            text += line+'\n';
        }
        std::cout << text << std::endl;
        parseCss(text);
        std::cout << "File " << filename << " loaded" << std::endl;
    }
    else
    {
        std::cout << "File " << filename << " could not be opened" << std::endl;
    }
    file.close();
}

void updateCss(std::string s, cssHandler* css);
void cssMgr::parseCss(std::string text){

    std::regex prop(R"(.*(\n)*\{(.*(\n)*)*?\})");
    std::smatch m;
    //std::cout << "CHUJ" << std::endl;

    while(std::regex_search(text, m, prop))
    {
        std::cout << "m.str(): " << m.str() << std::endl;
        std::string s = m.str();
        text = m.suffix();
        std::regex names(R"(^(.)*(\n)*\{)");
        std::smatch n;
        if(std::regex_search(s,n,names))
        {
            cssHandler* css = new cssHandler;

            std::string s2 = n.str();
            seekNames(s2,css);

            std::string s3 = n.suffix();
            std::regex atribs(R"(.+\:.+)");
            std::smatch k;
            while(std::regex_search(s3, k, atribs))
            {
                //std::cout << "k.str(): " << k.str() << std::endl;
                std::string o = k.str();
                updateCss(o, css);
                s3 = k.suffix();
            }
        }
    }
}

static std::vector<std::string> split(std::string strToSplit, char delimeter);
static std::string cleanWord(std::string text);

void updateCss(std::string s, cssHandler* css)
{
    s = cleanWord(s);
    std::vector<std::string> v = split(s, ' ');
    for(unsigned int i=0;i<v.size();i++)
    {
        v[i] = cleanWord(v[i]);
    }
    if(v.size()!=3)
    {
        std::cout << "Style improper" << std::endl;
        return;
    }
    css->changeAttribute(v[0],v[2]);
}

void cssMgr::seekNames(std::string text, cssHandler* css)
{
    text = cleanWord(text);
    std::vector<std::string> names = split(text, ',');
    for(auto i: names)
    {
        std::cout << "m: '" << i << "'" << std::endl;
        i = cleanWord(i);
        std::cout << "n: '" << i << "'" << std::endl;
        std::cout << "CLEAN: " << css << std::endl;
        //styles->insert_or_assign(i, css);
        (*styles)[i]= css;
        std::cout << "test" << std::endl;
        //std::cout << styles[i] << std::endl;
    }
}

cssHandler* cssMgr::getCss(std::string name)
{
    if(styles->find(name)!=styles->end())
        return styles->at(name);
    else
        return nullptr;
}

static std::vector<std::string> split(std::string strToSplit, char delimeter)
{
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter))
    {
       splittedStrings.push_back(item);
    }
    return splittedStrings;
}

static std::string cleanWord(std::string text)
{
    while(text.back()==' ' ||
          text.back()=='\n' ||
          text.back()=='{') text.pop_back();
    while(text.front()==' ' ||
          text.front()=='\n') text.erase(0,1);
    return text;
}
