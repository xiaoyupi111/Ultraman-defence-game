#ifndef ULTRAMANLEO_H
#define ULTRAMANLEO_H

#include "defencetower.h"

//艾斯奥特曼类
class UltraManLeo : public DefenceTower
{
public:
    int GetX() const;       //获取横坐标
    int GetY() const;       //获取横坐标
   UltraManLeo (int x, int y, int UMSLeftX, int UMSLeftY, int Swidth =120, int Sheight =120);
};
#endif // ULTRAMANLEO_H
