#include "selectionbox.h"

//构造
SelectionBox::SelectionBox(QString Path, int width, int height) :_w(width), _h(height), SelecBoxImgPath(Path) {}

int SelectionBox::GetX() const     //获取横坐标
{
    return _x;
}
int SelectionBox::GetY() const     //获取横坐标
{
    return _y;
}
int SelectionBox::GetWidth() const //获取宽
{
    return _w;
}
int SelectionBox::GetHeight() const //获取高
{
    return _h;
}

QString SelectionBox::GetImgPath() const    //返回选择框图片路径
{
    return SelecBoxImgPath;
}

//获取是否正在显示选择框
bool SelectionBox::GetDisplay() const
{
    return display;
}

//设置当前显示状态
void SelectionBox::SetDisplay(const bool SetPlay)
{
    display = SetPlay;
}

//选中防御塔，当选中防御塔时，才会显示选择框
void SelectionBox::CheckTower(int x, int y)//防御塔坐标，用来确定点在哪个防御塔上
{
    //确定选择框的位置
    _x = x - 95, _y = y - 95;

    SubBut[0].SubX = _x + 106, SubBut[0].SubY = _y + 14;//点击选择框后各个分按钮的位置
    SubBut[0].SubImgPath = QString(":/image/buyingtaro.png");

    SubBut[1].SubX = _x + 14, SubBut[1].SubY = _y + 106;//点击选择框后各个分按钮的位置
    SubBut[1].SubImgPath = QString(":/image/buyingseven.png");

    SubBut[2].SubX = _x + 202, SubBut[2].SubY = _y + 106;//点击选择框后各个分按钮的位置
    SubBut[2].SubImgPath = QString(":/image/buyingace.png");

    SubBut[3].SubX = _x + 106, SubBut[3].SubY = _y + 190;//点击选择框后各个分按钮的位置
    SubBut[3].SubImgPath = QString(":/image/buyingleo.png");


    display = true; //显示状态设为真
}

//获取子按钮结构数组
SubbutStr* SelectionBox::GetSelSubBut()
{
    return SubBut;
}
