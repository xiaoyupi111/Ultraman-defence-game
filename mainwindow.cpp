#include "mainwindow.h"
#include <QDebug>
#include "wholestruct.h"       //选择框按钮全局结构
#include <math.h>               //因为要运用到许多数学计算
#include "ultraman7.h"
#include"ultramantaro.h"
#include <QPushButton>
#include <QMediaPlayer>
#include <QSound>

//因为是绘制的格子，一个格子长度是40，所以要通过格子数来确定坐标
#define NewX(num) ((num) - 1) * 40 + 10

//插入怪物  路径点数组名、怪物初始坐标、怪物编号
#define InsterMonster(PathNum,StaCoorNum, MonsterId)     \
MonsterVec.push_back(new Monster(pointarr[PathNum], PathLength[PathNum], NewX(staco[StaCoorNum].x), NewX(staco[StaCoorNum].y), MonsterId));

//计算两点之间距离
#define DistBetPoints(X1, Y1, X2, Y2)           \
abs(sqrt((((X1) - (X2)) * ((X1) - (X2))) + (((Y1) - (Y2)) * ((Y1) - (Y2)))))

//判断鼠标点击位置（或者可以用监听）
#define MouClickRegion(X, Width, Y, Height)\
    (ev->x() >= (X) && ev->x() <= (X) + (Width) &&\
    ev->y() >= (Y) && ev->y() <= (Y) + (Height))


//构造
MainWindow::MainWindow()
{
    //设置固定窗口大小
    setFixedSize(1040, 640);

    //设置标题
    setWindowTitle("超决战！贝利亚银河帝国");

    //播放游戏音乐
    QSound *sound = new QSound(":/media/gamebgm.wav");
    sound->play();
    sound->setLoops(-1);//设置循环次数，-1为无限循环

    //胜利标签
    QLabel *victorylable = new QLabel(this);
    victorylable->move(176, 180);//显示位置
    setStyleSheet("color:red");
    victorylable->setFont(QFont("楷体", 110));//设置字体和大小
    victorylable->setText(QString("游戏胜利"));//设置文字
    victorylable->hide();

    //失败标签
    QLabel *falselable = new QLabel(this);
    falselable->move(176, 180);//显示位置
    setStyleSheet("color:black");
    falselable->setFont(QFont("楷体", 110));//设置字体和大小
    falselable->setText(QString("游戏失败"));//设置文字
    falselable->hide();

    QTimer* timer2 = new QTimer(this);      //怪物入场的定时器，以此来判断时候让什么怪兽入场
    timer2->start(2000);

    connect(timer2,&QTimer::timeout,[=]()
    {
            //设置路径点
            CoorStr* Waypointarr[] = {new CoorStr(NewX(8), NewX(6)), new CoorStr(NewX(2), NewX(6)), new CoorStr(NewX(3), NewX(13)), new CoorStr(NewX(13), NewX(13)), new CoorStr(NewX(13), NewX(9)), new CoorStr(homecoor->x, homecoor->y)};

            //怪物的2个起始点
            CoorStr staco[] = {CoorStr(8, 0), CoorStr(9, 0)};
            //每条路径的结点个数
            int PathLength[] = {sizeof(Waypointarr)/sizeof(CoorStr*), sizeof(Waypointarr)/sizeof(CoorStr*)};
            InsertMonster(Waypointarr, staco, PathLength, victorylable);   //产生怪物
    });

    //显示防御塔范围按钮
    QPushButton* disranpush = new QPushButton(this);
    disranpush->setStyleSheet("color:black");
    disranpush->setGeometry(20,80, 150, 45);
    disranpush->setFont(QFont("微软雅黑", 12));
    disranpush->setText("显示攻击范围");

    connect(disranpush,&QPushButton::clicked,[=]()
    {
        DisplayAllRange ? DisplayAllRange = false : DisplayAllRange = true;  //通过改变标识令防御塔攻击范围显示或关闭
        update();
    });

    //金钱标签
    moneylable->move(20, 20);       //位置
    setStyleSheet("color:white");   //设置颜色
    moneylable->setFont(QFont("楷体", 20));             //设置字体和大小
    moneylable->setText(QString("金钱：%1").arg(money));    //显示金钱信息

    //生命值标签
    QLabel *lifelable = new QLabel(this);
    lifelable->setGeometry(20, 40, 220, 40);   //设置标签位置和大小
    lifelable->setFont(QFont("楷体", 20));
    lifelable->setText(QString("生命：%1").arg(life));

    //定时器
    QTimer* timer = new QTimer(this);
    timer->start(120);
    connect(timer,&QTimer::timeout,[=]()
    {
        //找到出来的最后一个怪兽作为目标，目标死亡后找再继续找下一个（最后面）目标
        for (auto defei : DefeTowerVec)      //遍历防御塔
        {
            if (!defei->GetAimsMonster())   //若没有目标怪物为空时从后往前遍历怪物数组寻找目标怪物
            {
                for(int i = MonsterVec.size() - 1; i >= 0; i--)
                    //用防御塔中心店和怪兽中心点判断
                    if (DistBetPoints(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40,MonsterVec.at(i)->GetX() + (MonsterVec.at(i)->GetWidth() >> 1),
                        MonsterVec.at(i)->GetY() + (MonsterVec.at(i)->GetHeight() >> 1)) <= defei->GetRange())
                    {
                        defei->SetAimsMonster(MonsterVec.at(i));    //设置防御塔的目标怪物
                        break;
                    }
            }
            else                //如果拥有目标且目标在防御塔范围之内时时攻击目标
                if (DistBetPoints(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40,defei->GetAimsMonster()->GetX() + (defei->GetAimsMonster()->GetWidth() >> 1),
                    defei->GetAimsMonster()->GetY() + (defei->GetAimsMonster()->GetHeight() >> 1)) <= defei->GetRange())
                {
                    //根据每个防御塔的目标怪物计算旋转角度
                    defei->SetChangeAngle(atan2(defei->GetAimsMonster()->GetY() - defei->GetUpLeftY() + 40,defei->GetAimsMonster()->GetX()- defei->GetUpLeftX()) * 180 / 3.1415 );
                    defei->InterBullet();           //有目标就添加子弹
                }

            //判断目标存在时，防御塔攻击范围是否能够攻击到
            if (defei->GetAimsMonster())    //目标怪物不为空
                if (DistBetPoints(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40,defei->GetAimsMonster()->GetX() + (defei->GetAimsMonster()->GetWidth() >> 1),defei->GetAimsMonster()->GetY() + (defei->GetAimsMonster()->GetHeight() >> 1)) > defei->GetRange())
                        defei->SetAimsMonster(NULL);     //超过距离将目标怪物设为空
        }
        //怪物移动函数调用
        for (auto Moni = MonsterVec.begin(); Moni != MonsterVec.end(); Moni++)
            if((*Moni)->Move()) //怪物走到终点
            {
                delete *Moni;
                MonsterVec.erase(Moni);         //删除这个怪物

                life--;                         //生命-1
                lifelable->setText(QString("生命：%1").arg(life));//更新生命标签

                if (life <= 0)
                {
                    //生命值为0时提示游戏失败
                    falselable->show();
                }

                break;
            }
        update();
    });
}

//判断金钱是否足够并刷新标签
bool MainWindow::JudgeYourMoney(int money)
{
    if(this->money - money < 0) return true; //如果金钱足够
    this->money -= money; //那么扣除金钱
    moneylable->setText(QString("金钱：%1").arg(this->money)); //刷新金钱标签
    return false;
}
//插入怪物
void MainWindow::InsertMonster(CoorStr** Waypointarr, CoorStr* staco, int* PathLength, QLabel* victorylable)
{
    CoorStr** pointarr[] = {Waypointarr};
    if(counter >= 1 && counter <= 14)
    {
        InsterMonster(0,0,1); //第几条路径、第几个起始点、怪物编号
    }
    else if(counter > 14 && counter <= 34)
    {
        InsterMonster(0,0,2);

    }
    else if (counter > 34 && counter <= 52)
    {
        InsterMonster(0,0,1);
        InsterMonster(0,1,2);
    }
    if (counter > 55 && MonsterVec.empty())
        {
        //时间大于55且怪物数组中怪物时游戏胜利
        victorylable->show();
        }
    counter++;          //计数器+1
    update();
}

//根据数组画出地图函数
void MainWindow::DrawMapArr(QPainter& painter)
{
    //地图数组
    int Map[16][26] =
    {
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 3, 6, 1, 1, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 6, 6, 1, 1, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 3, 6, 0, 0, 3, 6, 0, 3, 6, 0, 0, 0, 0, 0,
        0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 6, 6, 0, 6, 6, 0, 0, 0, 0, 0,
        0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1,
        0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 0, 3, 6, 0, 0, 0, 0, 3, 6, 1, 1, 0, 0, 3, 6, 0, 0, 3, 6, 0, 0, 0, 0,
        0, 1, 1, 0, 6, 6, 0, 0, 0, 0, 6, 6, 1, 1, 0, 0, 6, 6, 0, 0, 6, 6, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

   //根据数字判断用switch语句判断该画什么
    for (int j = 0; j < 16; j++)
        for (int i = 0; i < 26; i++)
        {
            switch (Map[j][i])
            {
            case 0:     /*草地*/
                painter.drawPixmap(i*40, j*40, 40, 40,QPixmap(":/image/地砖.png"));
                break;
            case 1:     /*地面*/
                painter.drawPixmap(i*40, j*40, 40, 40,QPixmap(":/image/道路.png"));
                break;
            case 3:     /*防御塔坑*/
                painter.drawPixmap(i*40, j*40, 80, 80,QPixmap(":/image/召唤阵.png"));
                //防御塔坑坐标插入到塔坑对象数组
                TowerTankVec.push_back(new TowerTank(i*40, j*40));
                break;
            case 5:
                painter.drawPixmap(i*40, j*40, 40, 40, QPixmap(":/image/道路.png"));
                homecoor->x = i * 40, homecoor->y = j * 40;
                break;
            }
        }

    painter.drawPixmap(homecoor->x, homecoor->y, 80, 100,QPixmap(":/image/等离子火花塔.png"));//画出家
  }

//画出选择框
void MainWindow::DrawSelectionBox(QPainter& painter)
{
    //判断是否要显示选择框
    if (!SelBox->GetDisplay())
        return;

   //画出选择框
    painter.drawPixmap(SelBox->GetX(), SelBox->GetY(), SelBox->GetWidth(), SelBox->GetHeight(),QPixmap(SelBox->GetImgPath()));

    //画出子按钮
    SubbutStr *ASubBut = SelBox->GetSelSubBut();    //接收子按钮结构数组
    for (int i = 0; i < 4; i++)
    {
        painter.drawPixmap(ASubBut[i].SubX, ASubBut[i].SubY, ASubBut[i].SubWidth, ASubBut[i].SubHeight,QPixmap(ASubBut[i].SubImgPath));
    }

    painter.setPen(QPen(Qt::yellow, 6, Qt::SolidLine));     //设置画笔的状态
    painter.drawRect(QRect(SelBox->GetX() + 95, SelBox->GetY() + 95, 80, 80));
}

//画出防御塔
void MainWindow::DrawDefenseTower(QPainter& painter)
{
    //画出防御塔
    for (auto defei : DefeTowerVec)  //遍历防御塔数组
    {

        //画出所有防御塔的攻击范围
        if(DisplayAllRange)
            painter.drawEllipse(QPoint(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40), defei->GetRange(), defei->GetRange());

        //画出防御塔
        painter.translate(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40);          //设置旋转中心
        painter.rotate(defei->GetRotatAngle());             //旋转角度
        painter.translate(-(defei->GetUpLeftX() + 40), -(defei->GetUpLeftY() + 40));    //回到原点
        painter.drawPixmap(defei->GetX(), defei->GetY(), defei->GetWidth(), defei->GetHeight(), QPixmap(defei->GetDefImgPath()));

        painter.resetTransform();   //重置调整
    }
}

//画出怪物
void MainWindow::DrawMonster(QPainter& painter)
{
    for (auto moni : MonsterVec)//画出怪物
        painter.drawPixmap(moni->GetX(), moni->GetY(), moni->GetWidth(), moni->GetHeight(), QPixmap(moni->GetImgPath()));
}

//画出升级按钮以及防御塔攻击范围圈圈
void MainWindow::DrawRangeAndUpgrade(QPainter& painter)
{
    //画出防御塔攻击范围和升级按钮
    for (auto defei : DefeTowerVec)
        if(defei->GetUpLeftX() == DisplayRangeX && defei->GetUpLeftY() == DisplayRangeY && DisplayRange)
        {   //画出防御塔攻击范围
            painter.setPen(QPen(Qt::white));  //使用白色画出范围
            painter.drawEllipse(QPoint(DisplayRangeX + 40, DisplayRangeY + 40), defei->GetRange(), defei->GetRange());
            painter.drawPixmap(DisplayRangeX + 0, DisplayRangeY - 60, 90, 30, QPixmap(":/image/升级.png"));//画出升级按钮图片并设置大小和位置
        }
}
//绘图事件
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);     //创建画家类

    painter.setRenderHint(QPainter::Antialiasing);    //设置抗锯齿

    DrawMapArr(painter);        //画出地图

    DrawDefenseTower(painter);  //画出防御塔和子弹

    DrawMonster(painter);       //画出怪物

    DrawRangeAndUpgrade(painter);//画出攻击范围和升级按钮

    DrawSelectionBox(painter);  //画出选择框
}

//鼠标点击事件
void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() != Qt::LeftButton)
        return;

    //判断升级按钮的点击
    if (DisplayRange)
    {



    }

    //判断选择框四个子按钮的点击
    SubbutStr *ASubBut = SelBox->GetSelSubBut();
    for (int i = 0; i < 4; i++)
        if (MouClickRegion(ASubBut[i].SubX, ASubBut[i].SubWidth, ASubBut[i].SubY, ASubBut[i].SubHeight) && SelBox->GetDisplay())
        {
            SelBox->SetDisplay(false);      //取消显示选择框
            //防御塔子类
                if (JudgeYourMoney(160)) return;
                DefeTowerVec.push_back(new UltraMan7 (SelBox->GetX() + 110, SelBox->GetY() + 112, SelBox->GetX() + 95, SelBox->GetY() + 95, 72, 46));
                break;

            update();
            return;
        }

    //遍历所有塔坑
    for (auto APit : TowerTankVec)
        //判断点击塔坑
        if (MouClickRegion(APit->GetX(), APit->GetWidth(), APit->GetY(), APit->GetHeight()))
        {
            DisplayRange = false;               //降防御塔的升级选择显示关闭
            for (auto defei : DefeTowerVec)      //遍历数组判断防御塔坐标和点击坑坐标重合则返回
                if(defei->GetUpLeftX() == APit->GetX() && defei->GetUpLeftY() == APit->GetY())
                {
                    DisplayRangeX = defei->GetUpLeftX(), DisplayRangeY = defei->GetUpLeftY();   //记录要显示攻击范围的防御塔的坐标
                    DisplayRange = true;        //显示防御塔攻击范围
                    return;
                }

            SelBox->CheckTower(APit->GetX(), APit->GetY());  //选中防御塔，选择框显示
            update();

            return;
        }

    DisplayRange = false;           //取消显示防御塔攻击范围
    SelBox->SetDisplay(false);      //取消显示选择框

    update();
}



MainWindow::~MainWindow()
{
    //释放防御塔坑指针数组TowerPitVec
    for (auto it = TowerTankVec.begin(); it != TowerTankVec.end(); it++)
    {
        delete *it;
        *it = NULL;
    }

    //释放选择框类SelBox
    delete SelBox;
    SelBox = NULL;

    //释放防御塔父类指针数组DefeTowerVec
    for (auto it = DefeTowerVec.begin(); it != DefeTowerVec.end(); it++)
    {
        delete *it;
        *it = NULL;
    }

    //释放怪物数组MonsterVec
    for (auto it = MonsterVec.begin(); it != MonsterVec.end(); it++)
    {
        delete *it;
        *it = NULL;
    }

    delete homecoor;
}
