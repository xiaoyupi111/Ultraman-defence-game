#include "monster.h"
#include <QDebug>

//怪物类函数实现
Monster::Monster(CoorStr **pointarr, int num, int x, int y, int mid) :_x(x), _y(y), id(mid)
{
    for(int i = 0; i < num; i++)
    {
      //利用Waypoint来让怪兽入场，且waypoint是逆序链表,利用push_back逆序插入
      Waypoint.push_back(pointarr[i]);
    }

    //不同怪物赋值
    switch (id)
    {
    case 1:
        life = 200;   //生命值
        _attack=1;
        _w = 64, _h = 64; //宽高
        _speed=2;
        ImgPath = ":/image/monster1.png";
        PoisonImgPath=":/image/poisonmonster1.png";
        break;
    case 2:
        life = 400;
        _attack=1;
        _w = 64, _h = 64;
        _speed=2;
        ImgPath = ":/image/monster2.png";
        PoisonImgPath=":/image/poisonmonster2.png";
        break;
    case 3:
        life = 400;
        _attack=2;
        _w = 64, _h = 64;
        _speed=5;
        ImgPath = ":/image/monster3.png";
        PoisonImgPath=":/image/poisonmonster3.png";
        break;
    case 4:
        life = 1000;
        _attack=4;
        _w = 64, _h = 64;
        _speed=2;
        ImgPath = ":/image/monster4.png";
        PoisonImgPath=":/image/poisonmonster4.png";
        break;
    default:
        break;
    }
}
//怪物按设定路径点移动,路径点就是转折点
bool Monster::Move()
{
    if(Waypoint.empty())
        return true;

//每次都从第一个waypoint判断，在到达结点前走直线
    if (Waypoint.at(0)->y > _y) //下
    {
        _y += _speed;
        return false;
    }

    if (Waypoint.at(0)->x < _x) //左
    {
        _x -= _speed;
        return false;
    }

    if (Waypoint.at(0)->x > _x) //右
    {
        _x += _speed;
        return false;
    }

    if (Waypoint.at(0)->y < _y) //上
    {
        _y -= _speed;
        return false;
    }

    //如果怪物的坐标和路径点坐标重合，删除路径点，那么下一个路径点会成为需要判断的路径点，直到Waypoint数组清空
    if (Waypoint.at(0)->y == _y && Waypoint.at(0)->x == _x)
    {
        Waypoint.erase(Waypoint.begin());       //从数组中删除
        delete Waypoint.begin();                //释放坐标点内存
    }
    return false;
}


int Monster::GetX() const       //获取横坐标
{
    return _x;
}

int Monster::GetY() const       //获取横坐标
{
    return _y;
}

int Monster::GetWidth() const   //获取宽
{
    return _w;
}

int Monster::GetHeight() const  //获取高
{
    return _h;
}

QString Monster::GetImgPath() const //获取图片路径
{
    return ImgPath;
}
QString Monster::GetPoiImgPath()const
{
    return PoisonImgPath;
}
int Monster::GetId() const      //获取编号
{
    return id;
}

int Monster::GetLife() const  //获取生命值
{
    return life;
}

void Monster::SetLife(int hp)//设置生命值
{
    life = hp;
}
int Monster::GetAttack()const//获取怪兽攻击力
{
    return _attack;
}
int Monster::GetSpeed()const//获取速度
{
    return _speed;
}
void Monster::SetSpeed(int speed)//设置速度
{
    _speed=speed;
}
bool Monster::GetPoison()const//得到是否中毒
{
    return ispoison;
}
void Monster::SetPoison(bool poi)//设置是否中毒
{
    ispoison=poi;
}
bool Monster::GetRedSpeed()const//得到是否已经被减速
{
    return isredspeed;
}
void Monster::SetRedSpeed(bool redspeed)//设置是否被减速
{
    isredspeed=redspeed;
}
