#ifndef STRUCT_H
#define STRUCT_H

#include <QString>

//全局结构头文件，用来放非class而用struct的

//选择框子按钮
struct SubbutStr
{
    int SubX;           //子按钮相对选择框的横坐标
    int SubY;           //纵坐标
    int SubWidth = 56;  //子按钮宽
    int SubHeight = 56; //高
    QString SubImgPath; //子按钮的图片路径
};

//坐标（Qpoint也可以实现部分功能）
struct CoorStr
{
    int x;
    int y;
    CoorStr(int x1, int y1) : x(x1), y(y1) {}
};

//子弹
struct BulletStr
{
    CoorStr _coor;       //子弹坐标
    int k = 0, b = 0;   //用于计算出子弹路径函数
    bool dirflag = false;   //移动方向标识

    BulletStr(CoorStr coor) : _coor(coor) {}//子弹坐标初始化

    int GetX()  const
    {
        return _coor.x;
    }

    int GetY() const
    {
        return _coor.y;
    }
};

#endif // WHOLESTRUCT_H
