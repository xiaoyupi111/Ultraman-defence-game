#ifndef SELECTIONBOX_H
#define SELECTIONBOX_H

#include <QString>
#include "struct.h"   //全局结构

//选择框类
class SelectionBox
{
private:
    bool display = false;   //判断是否显示选择框
    int _x = 0, _y = 0;     //最左上角坐标
    const int _w, _h; //整体宽高
    QString SelecBoxImgPath;//选择框图片路径

    SubbutStr SubBut[4];    //子按钮-button

public:
    SelectionBox(QString Path, int width = 270, int height = 270);

    int GetX() const;     //获取横坐标
    int GetY() const;     //获取横坐标
    int GetWidth() const; //获取宽
    int GetHeight() const;//获取高
    QString GetImgPath() const; //获取选择框图片路径
    bool GetDisplay() const;  //获取显示状态
    void SetDisplay(const bool SetPlay); //设置显示状态
    void CheckTower(int x, int y); //选中防御塔
    SubbutStr* GetSelSubBut(); //获取子按钮结构数组
};

#endif // SELECTIONBOX_H
