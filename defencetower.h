#ifndef DEFENCETOWER_H
#define DEFENCETOWER_H

#include <QString>
#include "monster.h"    //怪物类头文件

//防御塔父类，这样可以让后续的几个防御塔少写点，直接公有继承
class DefenceTower
{
//防御塔属性
protected:
    int _x, _y;             //坐标
    int _w, _h;      //宽高
    QString DefImgPath;     //防御塔图片路径
    int ChangeAngle = 0;     //防御塔旋转角度
    int UpLeftX, UpLeftY;   //防御塔塔坑原坐标
    int Range;              //防御塔的射程

    Monster* aimsmon = NULL;//记录防御塔的目标怪物

    QString BullPath;       //子弹图片路径
    int power;              //子弹威力
    int bullwidth, bullheight;      //子弹宽高
    QVector<BulletStr*> BulletVec;  //子弹结构数组
    int counter = 0;        //用于控制发射子弹的速度
    int attack;             //防御塔攻击力

    int ExplRangeWidth;     //记录防御塔击中怪物后所能造成的爆炸效果的宽高
    int ExplRangeHeight;

public:
    int GetX() const;       //获取横坐标
    int GetY() const;       //获取横坐标
    int GetWidth() const;   //获取宽
    int GetHeight() const;  //获取高
    int GetRotatAngle() const;      //获取旋转角度
    QString GetBaseImgPath() const; //获取底座图片路径
    QString GetDefImgPath() const;  //获取防御塔图片路径
    int GetUpLeftX() const; //获取防御塔左上角原横坐标
    int GetUpLeftY() const; //获取防御塔左上角原纵坐标
    void SetChangeAngle(int ang);   //设置旋转角度
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
    //升级
    void SetAttack(int);            //设置防御塔攻击力
    void SetWidthHeight(int, int);  //设置防御塔宽高
    void SetXY(int, int);           //设置坐标
    int& SetRange();                //设置防御塔的攻击范围

    int GetExplRangeWidth() const;  //获取爆炸效果宽
    int GetExplRangeHeight() const; //获取爆炸效果高
    void SetExplRangeWidthHeight(int, int); //设置防御塔对应的爆炸效果的宽高

    void SetBulletWidthHeight(int, int);    //设置子弹宽高
};

#endif // DEFETOWERPARENT_H
