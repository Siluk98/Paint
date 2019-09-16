#include "../hpp/Canvas.hpp"
#include <iostream>
#include "../../Engine/hpp/event.hpp"
#include "../../Engine/hpp/game.hpp"
#include <queue>

using namespace UI;

unsigned int Canvas::brushSize = 6;
unsigned int Canvas::brushMax = 10;
sf::Color Canvas::paint(255,0,0);

Canvas::Canvas(){}

Canvas::Canvas(std::string id, int left, int top, unsigned int width, unsigned int height)
{
    std::cout << "cvConst: " << id << std::endl;
    this->width = width;
    this->height = height;
    drawspace = new sf::Image;
    drawspace->create(width, height, sf::Color::White);
    texture = new sf::Texture;
    texture->create(width, height);
    sprite = new sf::Sprite;
    sprite->setTexture(*texture);
    hitbox = new sf::IntRect(0,0,sprite->getTexture()->getSize().x,sprite->getTexture()->getSize().y);
    moveTo(left,top);
    this->id = id;
    addType("canvas");
    container = false;
    addEvent("MouseDown", Action{[](Object* a, Object* b, std::string arg1, std::string arg2){
                UI::Canvas *c = dynamic_cast<Canvas*>(a);
                sf::Vector2i mouse = sf::Mouse::getPosition(*Game::getWindow());
                sf::Vector2i pos;
                pos.x = mouse.x - c->sprite->getPosition().x;
                pos.y = mouse.y - c->sprite->getPosition().y;
                //c->drawCircle(pos.x,pos.y,brushSize);
                //c->floodfill(pos.x,pos.y);
                unsigned int brush = brushSize;
                while(brush!=0)
                {
                    c->drawDiamond(pos.x,pos.y,brush);
                    brush--;
                }
             }});
    std::cout << "cvConstEnd: " << id << std::endl;
}

Canvas::~Canvas(){};

void Canvas::update()
{
    for(unsigned int i=0;i<events.size();i++)
    {
        events[i]->handle(this,nullptr,"","");
    }
    texture->update(*drawspace);
}

void Canvas::collide(Object* collider){}
std::string Canvas::create(std::string obj, std::string params){return this->id;}
void Canvas::draw(sf::RenderTarget &target, sf::RenderStates s) const
{

    target.draw(*sprite);
}

void Canvas::drawCircle(int x0, int y0, int radius)
{
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x >= y)
    {
        drawPixel(x0 + x, y0 + y);
        drawPixel(x0 + y, y0 + x);
        drawPixel(x0 - y, y0 + x);
        drawPixel(x0 - x, y0 + y);
        drawPixel(x0 - x, y0 - y);
        drawPixel(x0 - y, y0 - x);
        drawPixel(x0 + y, y0 - x);
        drawPixel(x0 + x, y0 - y);

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }

        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}

void Canvas::drawDiamond(int x, int y, int r)
{
    drawspace->setPixel(x-1,y,paint);
    if(x-r<0 || y-r<0 || x+r>width || y+r>height) return;
    int cx = x-r;
    int cy = y;
    for(int j=r;j>0;j--)
    {
    for(int i=0;i<r-1;i++)
    {
        drawspace->setPixel(cx,cy,paint);
        cx++;
        cy--;
    }
    for(int i=0;i<r-1;i++)
    {
        drawspace->setPixel(cx,cy,paint);
        cx++;
        cy++;
    }
    for(int i=0;i<r-1;i++)
    {
        drawspace->setPixel(cx,cy,paint);
        cx--;
        cy++;
    }
    for(int i=0;i<r-1;i++)
    {
        drawspace->setPixel(cx,cy,paint);
        cx--;
        cy--;
    }
    }
}

void Canvas::drawPixel(unsigned int x, unsigned int y)
{
    //std::cout << x << " " << y << std::endl;
    if(x<0 || y<0 || x>width || y>height)
        return;
    drawspace->setPixel(x,y, paint);
}

void Canvas::floodfill(int x, int y)
{
    std::queue<sf::Vector2i> q;
    q.push(sf::Vector2i(x,y));
    int i=0;
    while(!q.empty())
    {
        std::cout << i++ << " " << q.size() << std::endl;
        unsigned int qx = q.front().x;
        unsigned int qy = q.front().y;
        q.pop();
        if(!(qx<0 || qy<0 || qx>width || qy>height))
            drawspace->setPixel(qx,qy,paint);
        if(!(qx-1<0 || qy<0 || qx-1>width || qy>height) && drawspace->getPixel(qx-1,qy)!=paint)
            q.push(sf::Vector2i(qx-1,qy));
        if(!(qx+1<0 || qy<0 || qx+1>width || qy>height) && drawspace->getPixel(qx+1,qy)!=paint)
            q.push(sf::Vector2i(qx+1,qy));
        if(!(qx<0 || qy-1<0 || qx>width || qy-1>height) && drawspace->getPixel(qx,qy-1)!=paint)
            q.push(sf::Vector2i(qx,qy-1));
        if(!(qx<0 || qy+1<0 || qx>width || qy+1>height) && drawspace->getPixel(qx+1,qy+1)!=paint)
            q.push(sf::Vector2i(qx,qy+1));
    }

}

void Canvas::clear()
{
    drawspace->create(width, height, sf::Color::White);
}

void Canvas::save(std::string name)
{
    drawspace->saveToFile(name);
}
void Canvas::load(std::string name)
{
    sf::Image temp;
    if(temp.loadFromFile(name))
        drawspace->loadFromFile(name);
    //improve
}

void Canvas::setColor(char r, char g, char b)
{
    paint.r = r;
    paint.g = g;
    paint.b = b;
}

void Canvas::brushDown(){
    brushSize--;
    if(brushSize<=0)
    {
        brushSize = 1;
    }
}

void Canvas::brushUp(){
    brushSize++;
    if(brushSize>brushMax)
    {
        brushSize = brushMax;
    }
}

void Canvas::changeStyle(std::string atr, std::string val)
{
    if(val == "") return;
    std::cout << id << ": " << atr << ": " << val << std::endl;
    if(atr == "width")
    {
        std::cout << "aasasasasas";
    }
    if(atr == "height")
    {
       std::cout << "dcdcdcdcdc";
    }
}
