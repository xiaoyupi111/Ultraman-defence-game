#ifndef ULTRAMANTARO_H
#define ULTRAMANTARO_H

#include "defencetower.h"

//泰罗奥特曼类，继承防御塔父类
class UltraManTaro : public DefenceTower
{
public:
    int GetX() const;       //获取横坐标
    int GetY() const;       //获取横坐标
    UltraManTaro (int x, int y, int UMSLeftX, int UMSLeftY, int Swidth =120, int Sheight =120);
};

#endif // ULTRAMANTARO_H
