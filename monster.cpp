#include "monster.h"
#include <QDebug>

//怪物类函数实现
Monster::Monster(CoorStr **pointarr, int arrlength, int x, int y, int mid) :
    _x(x), _y(y), id(mid)
{
    for(int i = 0; i < arrlength; i++)
    {
      //利用Waypoint来让怪兽入场，且waypoint是逆序链表，也就是说第一个点应该是home所在点
      Waypoint.push_back(pointarr[i]);
    }

    //不同怪物赋值
    switch (id)
    {
    case 1:
        life = 100;   //生命值
        _w = 64, _h = 64; //宽高
        _speed=8;
        ImgPath = ":/image/怪兽1.png";

        break;
    case 2:
        life = 120;
        _w = 84, _h = 64;
        _speed=12;
        ImgPath = ":/image/怪兽2.png";
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

    //如果第一个路径点的y小于怪物原本的路径点，则怪物向下走
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

    //如果怪物的坐标和路径点坐标重合，删除路径点，继续前行
    if (Waypoint.at(0)->y == _y && Waypoint.at(0)->x == _x)
    {
        delete Waypoint.begin();                //释放坐标点内存
        Waypoint.erase(Waypoint.begin());       //从数组中删除
        return false;
    }
}

//画出血条

 void Monster::drawHpRect(QPainter *painter)
{
        // 血条的长度
        // 其实就是2个方框,红色方框表示总生命,固定大小不变
        // 绿色方框表示当前生命,受currentHp / life的变化影响
        static const int Health_Width = 20;
        painter->save();
        QPoint healthBarPoint = QPoint(_x,_y)+ QPoint(-Health_Width / 2 - 5, _h/ 3);
        // 绘制血条
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::green);
        QRect healthBarBackRect(healthBarPoint, QSize(Health_Width, 2));
        painter->drawRect(healthBarBackRect);
        painter->setBrush(Qt::red);
        QRect healthBarRect(healthBarPoint, QSize((double)GetLife( )/ life* Health_Width, 2));
        painter->drawRect(healthBarRect);
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
int Monster::GetSpeed()const
{
    return _speed;
}
void Monster::SetSpeed(int speed)
{
    _speed=speed;
}
