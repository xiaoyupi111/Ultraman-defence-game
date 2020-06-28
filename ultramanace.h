#ifndef ULTRAMANACE_H
#define ULTRAMANACE_H

#include "defencetower.h"

//艾斯奥特曼类
class UltraManAce : public DefenceTower
{
public:
    int GetX() const;       //获取横坐标
    int GetY() const;       //获取横坐标
   UltraManAce (int x, int y, int UMSLeftX, int UMSLeftY, int Swidth =120, int Sheight =120);
};

#endif // ULTRAMANACE_H
