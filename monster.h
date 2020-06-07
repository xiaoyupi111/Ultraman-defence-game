#ifndef MONSTER_H
#define MONSTER_H

#include <QVector>
#include <QString>
#include <QPainter>
#include "wholestruct.h"   //全局坐标类

//怪兽类
class Monster
{
private:
    QVector<CoorStr*> Waypoint;  //用来存储怪物路径点的数组
    int _x, _y;                  //怪物坐标
    int _w, _h;         //怪物宽高
    QString ImgPath;             //怪物图片路径
    int id;                      //怪物编号
    int life;                  //怪物生命值
    int _speed;       //怪物移动速度
    int _attack;     //怪物攻击力

public:
    //参数：路径点数组、路径点的个数、怪物初始坐标、怪物宽度、怪物图片路径
    Monster(CoorStr **pointarr, int arrlength, int x, int y, int mid);  //构造
    bool Move();            //怪物移动函数
    void drawHpRect(QPainter *painter);

    int GetX() const;       //得到怪兽的横坐标
    int GetY() const;       //得到怪兽的纵坐标
    int GetWidth() const;   //获取宽
    int GetHeight() const;  //获取高
    QString GetImgPath() const; //得到怪兽的图片
    int GetId() const;      //获取编号
    void SetLife(int);    //设置生命值
    int GetLife() const;  //获取生命值
    void SetSpeed(int);//设置怪兽的移动速度
    int GetSpeed()const;//获取怪兽的移动速度
};

#endif // MONSTER_H
