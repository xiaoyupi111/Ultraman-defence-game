#ifndef DEFENCETOWER_H
#define DEFENCETOWER_H

#include <QString>
#include "monster.h"    //怪物类头文件

//防御塔父类，这样可以让后续的几个防御塔少写点，直接公有继承
class DefenceTower
{
//防御塔属性
public:
    virtual int GetX() const;       //获取横坐标
    virtual int GetY() const;       //获取横坐标
    virtual int GetWidth() const;   //获取宽
    virtual int GetHeight() const;  //获取高
    int GetRotatAngle() const; //获取旋转角度
    int GetUpLeftX() const; //获取防御塔左上角原横坐标
    int GetUpLeftY() const; //获取防御塔左上角原纵坐标
    void SetChangeAngle(int ang);   //设置旋转角度
    QString GetDefImgPath() const;  //获取防御塔图片路径

    int GetRange() const;   //设置防御塔的射程

    Monster* GetAimsMonster() const;//返回当前防御塔的目标怪物
    void SetAimsMonster(Monster*);  //设置当前防御塔的目标怪物

    QString GetBulletPath() const;  //返回防御塔子弹图片路径
    QVector<BulletStr*>& GetBulletVec();//返回子弹数组
    void InterBullet();             //新建子弹
    void BulletMove();              //子弹移动函数
    int GetBulletWidth() const;     //获取子弹的宽度
    int GetBulletHeight() const;    //获取子弹的宽度
    int GetAttack() const;          //防御塔攻击力
    int GetReduceSpeed() const;          //得到减速
    int GetPoisonHp()const;             //中毒效果


    //以下是升级时候需要设置的
    void SetReduceSpeed(int);            //设置减速
    void SetPoisonHp(int);               //设置中毒效果
    void SetAttack(int);            //设置防御塔攻击力
    void SetWidthHeight(int, int);  //设置防御塔宽高
    void SetXY(int, int);           //设置坐标
    int& SetRange();                //设置防御塔的攻击范围
    void SetBulletWidthHeight(int, int);    //设置子弹的形状，宽高放在一起

protected:
    int _x, _y;             //坐标
    int _w, _h;      //宽高
    int Range;              //防御塔的射程
    int ChangeAngle = 0;     //防御塔旋转角度
    int UpLeftX, UpLeftY;   //放置防御塔的坐标

    QString DefImgPath;     //防御塔图片路径

    //以下和子弹有关系
    Monster* targetmonster = NULL;//记录防御塔的目标怪物
    int power;              //子弹威力
    int bullwidth, bullheight;      //子弹宽高
    int counter = 0;        //计数
    int attack;             //防御塔攻击力
    int _reducespeed;       //减速效果
    int _poisonhp;          //中毒效果
    QString BullPath;       //子弹图片路径
    QVector<BulletStr*> BulletVec;  //存储子弹坐标的数组
};

#endif // DEFETOWERPARENT_H
