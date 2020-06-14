#include "ultramanace.h"

//艾斯奥特曼类函数实现(减速防御塔）
//构造
UltraManAce ::UltraManAce (int x, int y, int UMSLeftX, int UMSLeftY, int Swidth, int Sheight)
{
    _x = x, _y = y;//防御塔的位置初始化
    DefImgPath = QString(":/image/艾斯奥特曼.png");//指向防御塔图片路径
    _w = Swidth, _h = Sheight;//防御塔的长宽
    UpLeftX = UMSLeftX, UpLeftY = UMSLeftY;//防御塔左上角坐标

    BullPath = QString(":/image/减速子弹.png");//指向子弹图片的路径
    bullwidth = 30, bullheight = 30;           //固定子弹大小

    Range = 120;    //射程
    attack = 30;    //攻击力
    _reducespeed=2;  //减速效果
}
