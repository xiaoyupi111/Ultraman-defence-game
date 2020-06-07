#ifndef ULTRAMANTARO_H
#define ULTRAMANTARO_H

#include "defencetower.h"

//泰罗奥特曼类，继承防御塔父类（准备写成范围攻击，灼烧类型）
class UltraManTaro : public DefenceTower
{
public:
    UltraManTaro (int x, int y, int UMSLeftX, int UMSLeftY, int Swidth =300, int Sheight =300);
};

#endif // ULTRAMANTARO_H
