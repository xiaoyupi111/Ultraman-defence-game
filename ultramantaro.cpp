#include<ultramantaro.h>
//大射程
UltraManTaro::UltraManTaro(int x, int y, int UMSLeftX, int UMSLeftY, int Swidth, int Sheight)
{
    _x = x, _y = y;//防御塔的位置初始化
    _w = Swidth, _h = Sheight;//防御塔的长宽
    UpLeftX = UMSLeftX, UpLeftY = UMSLeftY;//防御塔左上角坐标，用来定位

    DefImgPath = QString(":/image/泰罗奥特曼一级.png");//指向防御塔图片路径

    BullPath = QString(":/image/子弹3.png");//指向子弹图片的路径
    bullwidth = 30, bullheight = 30;           //固定子弹大小
    Range = 180;    //射程
    attack = 40;    //攻击力
    _reducespeed=0;
}
