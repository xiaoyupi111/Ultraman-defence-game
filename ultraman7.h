#ifndef ULTRAMAN7_H
#define ULTRAMAN7_H

#include "defencetower.h"

//赛文奥特曼类，继承防御塔父类
class UltraMan7 : public DefenceTower
{
public:
    UltraMan7 (int x, int y, int UMSLeftX, int UMSLeftY, int Swidth =120, int Sheight =120);
};

#endif // ULTRAMAN7_H
