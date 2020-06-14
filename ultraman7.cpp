#include "ultraman7.h"

//赛文奥特曼类函数实现（纯攻击）
//构造
UltraMan7 ::UltraMan7 (int x, int y, int UMSLeftX, int UMSLeftY, int Swidth, int Sheight)
{
    _x = x, _y = y;//防御塔的位置初始化
    DefImgPath = QString(":/image/赛文奥特曼一级.png");//指向防御塔图片路径
    _w = Swidth, _h = Sheight;//防御塔的长宽
    UpLeftX = UMSLeftX, UpLeftY = UMSLeftY;//防御塔左上角坐标

    BullPath = QString(":/image/武器.png");//指向子弹图片的路径
    bullwidth = 50, bullheight = 50;           //固定子弹大小

    Range = 140;    //射程
    attack = 40;    //攻击力
    _reducespeed=0;  //减速效果
}
