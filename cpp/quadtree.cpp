#include "../hpp/quadtree.hpp"
#include <iostream>

QuadNode::QuadNode(int _x,int _y, int _x2,int _y2, std::vector<Object*>* _obj, QuadNode* _parent, int lvl, int lmax)
{
    //std::cout << "Node created: " << _x << "," << _y << " " << _x2 << "," << _y2 << std::endl;
    parent = parent;
    obj = _obj;
    x1 = _x;
    y1 = _y;
    x2 = _x2;
    y2 = _y2;
    xd = std::abs(x2-x1);
    yd = std::abs(y2-y1);
    level = lvl;
    levelMax = lmax;
    for(int i=0;i<4;i++)
    {
        children[i] = nullptr;
    }
    if(obj->size()>1)
    {
        if(level < levelMax)
        {
            divide();
        }
        else
        {
            for(auto j:(*obj))
            {
                for(auto i:(*obj))
                {
                    if(i!=j)
                    {
                        std::cout << "collide" <<std::endl;
                        j->collide(i);
                    }
                }
            }
        }
    }
}

QuadNode::~QuadNode()
{
    //std::cout << "Node deleted: " << x1 << "," << y1 << " " << x2 << "," << y2 << std::endl;
    for(int i=0;i<4;i++)
    {
        delete children[i];
    }
}

void QuadNode::divide()
{
    //std::cout << "c0:" << getObjsContained(obj,x1,y1,xd/2,yd/2)->size() << std::endl;
    //std::cout << "c1:" << getObjsContained(obj,x1+xd/2,y1,xd/2,yd/2)->size() << std::endl;
    //std::cout << "c2:" << getObjsContained(obj,x1,y1-yd/2,xd/2,yd/2)->size() << std::endl;
    //std::cout << "c3:" << getObjsContained(obj,x1+xd/2,y1-yd/2,xd/2,yd/2)->size() << std::endl;
    children[0] = new QuadNode(x1,y1,x1+xd/2,y1+yd/2,getObjsContained(obj,x1,y1,xd/2,yd/2), this,level+1, levelMax);
    children[1] = new QuadNode(x1+xd/2,y1,x1+xd,y1+yd/2,getObjsContained(obj,x1+xd/2,y1,xd/2,yd/2), this,level+1, levelMax);
    children[2] = new QuadNode(x1,y1+yd/2,x1+xd/2,y1+yd,getObjsContained(obj,x1,y1+yd/2,xd/2,yd/2), this,level+1, levelMax);
    children[3] = new QuadNode(x1+xd/2,y1+yd/2,x1+xd,y1+yd,getObjsContained(obj,x1+xd/2,y1+yd/2,xd/2,yd/2), this,level+1, levelMax);
}

std::vector<Object*>* QuadNode::getObjsContained(std::vector<Object*>* obj, int x, int y, int xl, int yl)
{
    std::vector<Object*>* v = new std::vector<Object*>;
    sf::IntRect r(x,y,xl,yl);
    for(auto o:(*obj))
    {
        if(r.intersects(*(o->getHitbox())))
           {
               v->push_back(o);
           }
    }
    return v;
}

Quadtree::Quadtree(std::vector<Object*>* obj, sf::RenderWindow* window, int lvl)
{
    auto wsize = window->getSize();
    head = new QuadNode(0,0,wsize.x,wsize.y,obj, nullptr, 0, lvl);
}

Quadtree::~Quadtree()
{
    delete head;
}
