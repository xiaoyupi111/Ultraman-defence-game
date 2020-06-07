#ifndef TOWERTANK_H
#define TOWERTANK_H

#include <QVector>

//防御塔槽类
class TowerTank
{
private:
    const int _x, _y;           //位置坐标
    const int _w, _h;  //宽高

public:
    //构造    参数：防御塔坑坐标、宽高
    TowerTank(int x, int y, int w=80, int h=80);

    int GetX() const;     //获取横坐标
    int GetY() const;     //获取横坐标
    int GetWidth() const; //获取宽
    int GetHeight() const;//获取高
};

#endif //TOWERTANK_H
