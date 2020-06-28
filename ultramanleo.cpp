#include "ultramanleo.h"

//雷欧奥特曼类函数实现(中毒防御塔）
//构造
UltraManLeo ::UltraManLeo (int x, int y, int UMSLeftX, int UMSLeftY, int Swidth, int Sheight)
{
    _x = x, _y = y;//防御塔的位置初始化
    DefImgPath = QString(":/image/leo.png");//指向防御塔图片路径
    _w = Swidth, _h = Sheight;//防御塔的长宽
    UpLeftX = UMSLeftX, UpLeftY = UMSLeftY;//防御塔左上角坐标

    BullPath = QString(":/image/bullet4.png");//指向子弹图片的路径
    bullwidth = 30, bullheight = 30;           //固定子弹大小

    Range = 120;    //射程
    attack = 0;    //攻击力
    _reducespeed=0;  //减速效果
    _poisonhp=10;//中毒效果
}
int UltraManLeo::GetX() const     //获取横坐标
{
    return _x;
}

int UltraManLeo::GetY() const     //获取横坐标
{
    return _y;
}
