#include "towertank.h"

//放置防御塔的坑类的函数实现
TowerTank::TowerTank(int x,int y,int w,int h): _x(x), _y(y), _w(w), _h(h) {}

int TowerTank::GetX() const     //得到坑的横坐标
{
    return _x;
}

int TowerTank::GetY() const     //得到坑的纵坐标
{
    return _y;
}

int TowerTank::GetWidth() const //得到坑的宽度
{
    return _w;
}

int TowerTank::GetHeight() const //得到坑的高度
{
    return _h;
}

