#ifndef PREDICATES_HPP
#define PREDICATES_HPP
#include "event.hpp"
#include "eventMgr.hpp"

void initDefaultPredicates(Game* game, eventMgr* mgr)
{
    mgr->addPredicate("pred", Predicate {[](Object* a,Object* b,std::string arg1, std::string arg2)->bool{
        if(a->getSprite()!=nullptr)
        {
            if(a->getSprite()->getPosition().y<100)return true;
            else return false;
        }else return false;
        }});

    mgr->addPredicate("MouseDown", Predicate{[](Object* a, Object* b,std::string arg1, std::string arg2){
            Game* game = Game::getGame();
            //std::cout << "t1";
            if(game!=nullptr && game->getWindow() != nullptr)
            {
                //std::cout << "2";
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    //std::cout << "3";
                    if(a != nullptr )
                    {
                        //std::cout << "4";
                        sf::IntRect* hitbox = a->getHitbox();
                        auto pos = sf::Mouse::getPosition(*(game->getWindow()));
                        /*std::cout << "mouse pos x:" << pos.x << "y:" << pos.y << std::endl;
                        std::cout << "lef: " << hitbox->left << std::endl;
                        std::cout << "top: " << hitbox->top << std::endl;
                        std::cout << "wid: " << hitbox->width << std::endl;
                        std::cout << "hei: " << hitbox->height << std::endl;
                        */
                        if(pos.y >= hitbox->left &&
                           pos.y <= hitbox->left+hitbox->width &&
                           pos.x >= hitbox->top &&
                           pos.x <= hitbox->top+hitbox->height) return true;
                    }
                }
            };
            return false;
            }});

    mgr->addPredicate("MouseUp", Predicate{[](Object* a, Object* b, std::string arg1, std::string arg2){
        Game* game = Game::getGame();
        if(game!=nullptr && game->getWindow() != nullptr)
            {
                //std::cout << "2";
                if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    //std::cout << "3";
                    if(a != nullptr )
                    {
                        //std::cout << "4";
                        sf::IntRect* hitbox = a->getHitbox();
                        auto pos = sf::Mouse::getPosition(*(game->getWindow()));
                        /*std::cout << "mouse pos x:" << pos.x << "y:" << pos.y << std::endl;
                        std::cout << "lef: " << hitbox->left << std::endl;
                        std::cout << "top: " << hitbox->top << std::endl;
                        std::cout << "wid: " << hitbox->width << std::endl;
                        std::cout << "hei: " << hitbox->height << std::endl;
                        */
                        if(pos.y >= hitbox->left &&
                           pos.y <= hitbox->left+hitbox->width &&
                           pos.x >= hitbox->top &&
                           pos.x <= hitbox->top+hitbox->height) return true;
                    }
                }
            };
            return false;
    }});
}

#endif // PREDICATES_HPP
