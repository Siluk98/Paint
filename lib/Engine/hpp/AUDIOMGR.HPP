#ifndef AUDIOMGR_HPP
#define AUDIOMGR_HPP

#include <map>
#include <SFML/Audio.hpp>

class audioMgr
{
public:
    audioMgr();
    ~audioMgr();
    void loadSoundFromFile(std::string file ,std::string name);
    void loadMusicFromFile(std::string file);
    void playMusic();
    void playSound(std::string);
    //audioMgr* const getInstance();
private:
    std::map<std::string,sf::Sound*> sounds;
    sf::Music music;
    //audioMgr* instance;
};

#endif
