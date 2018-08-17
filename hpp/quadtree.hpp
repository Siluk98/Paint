#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include "object.hpp"

class QuadNode
{
public:
    QuadNode(int x,int y, int x2,int y2, std::vector<Object*>* obj, QuadNode* parent, int lvl, int lmax);
    ~QuadNode();
private:
    void divide();
    QuadNode* parent;
    QuadNode* children[4];
    std::vector<Object*>* obj;
    int x1;
    int x2;
    int y1;
    int y2;
    int xd;
    int yd;
    int level;
    int levelMax;
    std::vector<Object*>* getObjsContained(std::vector<Object*>* obj, int x, int y, int xl, int yl);
    void collide(std::vector<Object*> &obj);
};

class Quadtree
{
public:
    Quadtree(std::vector<Object*>* obj, sf::RenderWindow* window, int lvl);
    ~Quadtree();
private:
    QuadNode* head;
};

#endif // QUADTREE_HPP
