#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPainter>     //画家
#include <QMouseEvent>  //鼠标事件
#include <Qtimer>       //Qtimer用来定时，控制怪兽入场波次和刷新页面
#include "towertank.h"    //防御塔坑类
#include "selectionbox.h"       //选择框类
#include "defencetower.h"    //防御塔父类
#include "monster.h"    //怪物类
#include <QLabel>        //写金币和生命啥的
#include <QKeyEvent>

class MainWindow : public QWidget
{
//    Q_OBJECT
private:
    QVector<TowerTank*> TowerTankVec;  //防御塔卡槽数组
    QVector<DefenceTower*> DefeTowerVec; //防御塔父类数组
    QVector<Monster*> MonsterVec;           //怪物数组

    void mousePressEvent(QMouseEvent *);    //鼠标点击事件

    //以下为绘图函数
    void paintEvent(QPaintEvent *);         //绘图事件
    void DrawMapArr(QPainter&);             //画出地图
    void DrawSelectionBox(QPainter&);       //画出选择框
    void DrawDefenseTower(QPainter&);       //画出防御塔
    void DrawMonster(QPainter&);            //画出怪物
    void DrawRangeAndUpgrade(QPainter&);    //画出防御塔攻击范围和升级按钮
    void DrawDestroyTower(QPainter&);

    int DisplayRangeX, DisplayRangeY;       //记录正在显示范围的防御塔的坐标，以便开关
    bool DisplayRange = false;              //用于显示防御塔攻击范围，初始都是false，就是关闭着的
    bool playmusic=true;//控制播放音乐

    int money = 1000;   //记录金钱
    QLabel *moneylable = new QLabel(this);   //显示金钱标签控件

    inline bool JudgeYourMoney(int);         //判断金钱是否足够购买并更新金币标签

    int life = 10;      //生命数量

    void InsertMonster(CoorStr**, CoorStr*, int, QLabel*);

    int counter = 0;    //产生怪兽的计数器

    int RewardMoney = 40; //每次击败怪兽获得的金钱数量

    CoorStr *homecoor = new CoorStr(0, 0);  //记录被保护的目标的坐标，coorstr是坐标Struct，从地图中实时获取

    bool DisplayAllRange = false;  //是否显示所有防御塔的攻击范围的标识
    SelectionBox* SelBox = new SelectionBox(":/image/选择框.png"); //显示选择框

public:
    MainWindow();            //构造
    ~MainWindow();
};

#endif  //MAINWINDOW_H
