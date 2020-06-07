#include "defencetower.h"

int DefenceTower::GetX() const     //获取横坐标
{
    return _x;
}

int DefenceTower::GetY() const     //获取横坐标
{
    return _y;
}

int DefenceTower::GetWidth() const //获取宽
{
    return _w;
}

int DefenceTower::GetHeight() const //获取高
{
    return _h;
}

int DefenceTower::GetRotatAngle() const//获取旋转角度
{
    return ChangeAngle;
}

QString DefenceTower::GetDefImgPath() const   //获取防御塔图片路径
{
    return DefImgPath;
}

int DefenceTower::GetUpLeftX() const     //获取防御塔左上角原横坐标
{
    return UpLeftX;
}

int DefenceTower::GetUpLeftY() const     //获取防御塔左上角原纵坐标
{
    return UpLeftY;
}

void DefenceTower::SetChangeAngle(int ang)    //设置旋转角度
{
    ChangeAngle = ang;
}

int DefenceTower::GetRange() const           //获取防御塔射程
{
    return Range;
}

Monster* DefenceTower::GetAimsMonster() const //返回当前防御塔的目标怪物
{
    return aimsmon;
}

void DefenceTower::SetAimsMonster(Monster* mon)  //设置当前防御塔的目标怪物
{
    aimsmon = mon;
}

QString DefenceTower::GetBulletPath() const      //返回防御塔子弹图片路径
{
    return BullPath;
}

QVector<BulletStr*>& DefenceTower::GetBulletVec()//返回子弹数组
{
    return BulletVec;
}

void DefenceTower::InterBullet()     //新建子弹函数
{


}

void DefenceTower::BulletMove()         //子弹移动函数
{


}

int DefenceTower::GetBulletWidth() const //获取子弹的宽度
{
    return bullwidth;
}

int DefenceTower::GetBulletHeight() const//获取子弹的宽度
{
    return bullheight;
}

int DefenceTower::GetAttack() const      //获取防御塔攻击力
{
    return attack;
}

void DefenceTower::SetAttack(int attack)       //设置防御塔攻击力
{
    this->attack = attack;
}

void DefenceTower::SetWidthHeight(int width, int height)  //设置防御塔宽高
{
    this->_w = width, this->_h= height;
}

void DefenceTower::SetXY(int x, int y)       //设置坐标
{
    this->_x = x, this->_y = y;
}

int& DefenceTower::SetRange()                //设置防御塔的攻击范围
{
    return Range;
}

void DefenceTower::SetBulletWidthHeight(int width, int height)         //设置子弹宽高
{
    bullwidth = width, bullheight = height;
}











