#include "mainwindow.h"
#include <QDebug>
#include "struct.h"       //选择框按钮全局结构
#include <math.h>               //因为要运用到许多数学计算
#include "ultraman7.h"
#include<start.h>
#include"ultramantaro.h"
#include"ultramanace.h"
#include"ultramanleo.h"
#include <QPushButton>
#include <QSound>
#include <QPainter>
#include <windows.h>

//计算两点之间距离
#define Distance(X1, Y1, X2, Y2)           \
abs(sqrt((((X1) - (X2)) * ((X1) - (X2))) + (((Y1) - (Y2)) * ((Y1) - (Y2)))))


//构造
MainWindow::MainWindow(int Number):Number(Number)
{
    //设置固定窗口大小
    setFixedSize(1040, 640);

    //设置标题
    setWindowTitle("超決戦ベリア銀河帝国");

    //进入游戏界面就开始播放音乐
    QPushButton* mediaplay = new QPushButton(this);
    mediaplay->setStyleSheet("color:black");
    mediaplay->setGeometry(830,120, 150, 45);
    mediaplay->setFont(QFont("幼圆", 12));
    mediaplay->setText("音楽再生");
    QSound *sound = new QSound(":/media/gamebgm.wav");
    sound->play();
    sound->setLoops(-1);//设置循环次数，-1为无限循环

    //播放游戏音乐按钮
    connect(mediaplay,&QPushButton::clicked,[=]()
    {
        playmusic ? playmusic= false: playmusic = true;
        if(playmusic==true)
        {
            sound->play();
            sound->setLoops(-1);//设置循环次数，-1为无限循环
        }
        else//停止播放音乐
        {
            sound->stop();
        }
        update();
    });

    //胜利标签
    QLabel *victorylable = new QLabel(this);
    victorylable->move(460, 180);//显示位置
    setStyleSheet("color:red");
    victorylable->setFont(QFont("幼圆", 110));//设置字体和大小
    victorylable->setText(QString("勝利"));//设置文字
    victorylable->hide();

    //失败标签
    QLabel *falselable = new QLabel(this);
    falselable->move(460, 180);//显示位置
    setStyleSheet("color:black");
    falselable->setFont(QFont("幼圆", 110));//设置字体和大小
    falselable->setText(QString("失敗"));//设置文字
    falselable->hide();

    //显示防御塔范围按钮
    QPushButton* disranpush = new QPushButton(this);
    disranpush->setStyleSheet("color:black");
    disranpush->setGeometry(830,80, 150, 45);
    disranpush->setFont(QFont("幼圆", 12));
    disranpush->setText("攻撃範囲を表示");
    connect(disranpush,&QPushButton::clicked,[=]()
    {
        DisplayAllRange ? DisplayAllRange = false : DisplayAllRange = true;  //通过改变标识令防御塔攻击范围显示或关闭
        update();
    });

    //金币
    moneylable->move(830,15) ;      //位置
    setStyleSheet("color:white");   //设置颜色
    moneylable->setFont(QFont("幼圆", 20));             //设置字体和大小
    moneylable->setText(QString("金貨：%1").arg(money));    //显示金钱信息

    //生命值
    QLabel *lifelable = new QLabel(this);
    lifelable->setGeometry(830, 40, 220, 40);   //设置标签位置和大小
    lifelable->setFont(QFont("幼圆", 20));
    lifelable->setText(QString("生命値：%1").arg(life));

    //怪物入场的定时器，以此来判断时候让什么怪兽入场
    QTimer* timer2 = new QTimer(this);
    timer2->start(3000);//3000ms也就是3s
    connect(timer2,&QTimer::timeout,[=]()
    {
        switch (Number)
        {
        case 0:
            {
            //设置路径点
            CoorStr* Waypointarr[4]= {new CoorStr(290, 490), new CoorStr(610, 490), new CoorStr(610, 330), new CoorStr(homecoor->x, homecoor->y)};
            //怪物的2个起始点
            CoorStr staco[] = {CoorStr(290, -30), CoorStr(290,-70)};
            //转折点的个数
            int PathLength= sizeof(Waypointarr)/sizeof(CoorStr*);
            InsertMonster(Waypointarr, staco, PathLength, victorylable);   //产生怪物
            break;
            }
        case 1:
        {
            //设置路径点
            CoorStr* Waypointarr[5]= {new CoorStr(130, 290), new CoorStr(770, 290), new CoorStr(770, 490), new CoorStr(210, 490),new CoorStr(homecoor->x, homecoor->y)};
            //怪物的2个起始点
            CoorStr staco[] = {CoorStr(130, -30), CoorStr(130,-70)};
            //转折点的个数
            int PathLength= sizeof(Waypointarr)/sizeof(CoorStr*);
            InsertMonster(Waypointarr, staco, PathLength, victorylable);   //产生怪物
            break;
        }
        default:
            break;
            }
    });

    //防御塔更新的定时器
    QTimer* timer = new QTimer(this);
    timer->start(60);//60ms更新一次
    connect(timer,&QTimer::timeout,[=]()
    {
        //防御塔寻找目标怪物的规律：找到最后一个怪物作为目标，目标丢失后找再继续找最后一个目标
        for (auto defei : DefeTowerVec)      //遍历防御塔
        {
            if (!defei->GetAimsMonster())   //防御塔没有目标怪兽时，从后往前遍历怪物数组寻找目标怪物
            {
                for(int i = MonsterVec.size() - 1; i >= 0; i--)
                    //防御塔中心点和怪物的中心点计算距离， 假如两者距离在范围内
                    if (Distance(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40,MonsterVec.at(i)->GetX() + (MonsterVec.at(i)->GetWidth() >> 1),MonsterVec.at(i)->GetY() + (MonsterVec.at(i)->GetHeight() >> 1)) <= defei->GetRange())
                    {
                        defei->SetAimsMonster(MonsterVec.at(i));    //设置防御塔的目标怪物
                        break;  //找到后跳出循环
                    }
            }
            else                //当前防御塔拥有目标且怪物在防御塔范围之内时时攻击怪物
                if (Distance(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40,
                    defei->GetAimsMonster()->GetX() + (defei->GetAimsMonster()->GetWidth() >> 1),
                    defei->GetAimsMonster()->GetY() + (defei->GetAimsMonster()->GetHeight() >> 1)) <= defei->GetRange())
                {
                    //根据每个防御塔的目标怪物计算旋转角度
                    defei->SetChangeAngle(atan2(defei->GetAimsMonster()->GetY()- defei->GetUpLeftY() + 40,defei->GetAimsMonster()->GetX()- defei->GetUpLeftX()) * 180 / 3.1415 );
                     defei->InterBullet();           //拥有目标时一直创建子弹
                }

            //判断怪物是否在防御塔攻击范围内
            if (defei->GetAimsMonster())    //假如存在目标怪物，那么判断怪物是否在攻击范围内
                if (Distance(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40,
                    defei->GetAimsMonster()->GetX() + (defei->GetAimsMonster()->GetWidth() >> 1),
                    defei->GetAimsMonster()->GetY() + (defei->GetAimsMonster()->GetHeight() >> 1)) > defei->GetRange())
                        defei->SetAimsMonster(NULL);     //超过距离将目标怪物设为空
        }

        //判断子弹是否击中怪物
        for (auto defei : DefeTowerVec)  //防御塔
        {
            auto &tbullvec = defei->GetBulletVec();    //存储子弹
            for (auto bullit = tbullvec.begin(); bullit != tbullvec.end(); bullit++)    //遍历子弹数组
                for (auto monit = MonsterVec.begin(); monit != MonsterVec.end(); monit++)//怪物
                    if ((*bullit)->GetX() + (defei->GetBulletWidth() >> 1) >= (*monit)->GetX() && (*bullit)->GetX() <= (*monit)->GetX() + (*monit)->GetWidth() &&
                       (*bullit)->GetY() + (defei->GetBulletHeight() >> 1) >= (*monit)->GetY() && (*bullit)->GetY() <= (*monit)->GetY() + (*monit)->GetHeight())
                    {   //击中怪物时
                        tbullvec.erase(bullit);     //删除子弹

                        (*monit)->SetLife((*monit)->GetLife() - defei->GetAttack());      //敌人血量 = 本身血量-当前炮塔攻击力
                       if((*monit)->GetRedSpeed()==false && (*monit)->GetSpeed()>2&&defei->GetReduceSpeed()!=0 && (*monit)->GetLife() >= 0)//假如敌人速度大于2且没有被减速那么减速炮塔发挥减速作用
                       {
                           (*monit)->SetRedSpeed(true);
                           int currents=(*monit)->GetSpeed();
                           (*monit)->SetSpeed((*monit)->GetSpeed() - defei->GetReduceSpeed());
                           QTimer::singleShot(600,this,[=](){
                               (*monit)->SetSpeed(currents);
                               (*monit)->SetRedSpeed(false);//重新将怪物的减速状态设为未减速
                           });

                       }
                       if(defei->GetPoisonHp()!=0&&(*monit)->GetPoison()==false && (*monit)->GetLife() >= 0)//假如当前怪物没有中毒,那么炮塔使其中毒
                       {                           
                               (*monit)->SetPoison(true);//设置成已中毒
                               (*monit)->SetLife((*monit)->GetLife() - defei->GetPoisonHp());
                       }
                       if((*monit)->GetPoison()==true&& (*monit)->GetLife() >= 0)//假如已经中毒，直接扣血
                       {
                           (*monit)->SetLife((*monit)->GetLife() - defei->GetPoisonHp());
                       }

                        if ((*monit)->GetLife() <= 0) //生命值为空时
                        {
                            //判断是否存在其他防御塔的目标怪物也为当前怪物，如果有，也设置为空
                            for (auto defei2 : DefeTowerVec)
                            {
                                if (defei2->GetAimsMonster() == *monit)
                                {
                                    defei2->SetAimsMonster(NULL);
                                }

                            }
                            delete *monit;
                            MonsterVec.erase(monit);    //删除怪物
                            money += RewardMoney;       //击败怪物增加金钱
                            moneylable->setText(QString("金貨：%1").arg(money));//刷新标签
                        }

                        //子弹攻击到的怪物不一定是防御塔的目标怪物，还需要进一步判断
                        goto L1;
                    }
            L1:;
        }

        //防御塔子弹移动
        for (auto defei : DefeTowerVec)
            defei->BulletMove();

        //调用怪物移动函数，判断怪物是否走到终点需要删除
        for (auto monsteri = MonsterVec.begin(); monsteri!= MonsterVec.end(); monsteri++)
        {
            if((*monsteri)->Move()) //当怪物走到终点无法再移动时
            {

                delete *monsteri;//释放空间
                MonsterVec.erase(monsteri);//删除怪物

                life=life-(*monsteri)->GetAttack();                    //生命=生命-怪兽攻击力
                lifelable->setText(QString("生命値：%1").arg(life));//更新生命值

                if (life <= 0)
                    {
                    falselable->show();//生命值为0时弹出游戏失败窗口
                    QTimer::singleShot(3000,this,[=](){
                        this->close();
                    });
                    }

                break;
            }
        }
        update();   //绘图
    });
}
//判断金钱是否足够并刷新标签
bool MainWindow::JudgeYourMoney(int money)
{

    if(this->money - money < 0) return true; //如果金钱足够
    this->money -= money; //那么扣除金钱
    moneylable->setText(QString("金貨：%1").arg(this->money)); //刷新金钱标签
    return false;
}

//插入怪物
void MainWindow::InsertMonster(CoorStr** Waypointarr, CoorStr* staco, int PathLength, QLabel* victorylable)
{
    CoorStr** pointarr= Waypointarr;

    if(counter >= 1 && counter <= 9)
    {
        MonsterVec.push_back(new Monster(pointarr, PathLength, staco[0].x, staco[0].y,1));
    }

    else if(counter > 9 && counter <= 30)
    {
        MonsterVec.push_back(new Monster(pointarr, PathLength, staco[0].x, staco[0].y,1));
        MonsterVec.push_back(new Monster(pointarr, PathLength, staco[1].x, staco[1].y,2));
    }
    else if (counter > 30 && counter <= 48){
        MonsterVec.push_back(new Monster(pointarr, PathLength, staco[0].x, staco[0].y,3));
    }

    else if (counter > 48 && counter <= 66)
    {
        MonsterVec.push_back(new Monster(pointarr, PathLength, staco[0].x, staco[0].y,4));
    }

    if (counter > 66 && MonsterVec.empty())//时间大于76且怪物数组为空时游戏胜利
        {
        victorylable->show();      
        QTimer::singleShot(3000,this,[=](){
            this->close();
        });
        }

    counter++;          //计数器+1
    update();
}

//根据数组画出地图函数
void MainWindow::DrawMapArr(QPainter& painter)
{
    //地图数组
    int Map_1[16][26] =
    {
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 3, 6, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 6, 6, 1, 1, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 3, 6, 1, 1, 0, 0, 0, 0, 0, 0, 0, 3, 6, 0, 3, 6, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 6, 6, 1, 1, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 6, 6, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 3, 6, 1, 1, 0, 3, 6, 0, 0, 0, 1, 1, 3, 6, 0, 0, 3, 6, 0, 0, 0,
        0, 0, 0, 0, 0, 6, 6, 1, 1, 0, 6, 6, 0, 0, 0, 1, 1, 6, 6, 0, 0, 6, 6, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    //第二关
    int Map_2[16][26] =
    {
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 3, 6, 0, 0, 3, 6, 0, 0, 0, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 6, 6, 0, 0, 6, 6, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 6, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 0, 0, 0,
        0, 0, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 6, 6, 0, 3, 6, 0, 0, 0, 0, 3, 6, 0, 0, 0, 0, 3, 6, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 6, 6, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    int Map[16][26];    //单拿出来一个数组用来copy哪一关,方便后续绘图

    switch (Number)
    {
    case 0:
        memcpy(Map, Map_1, sizeof(Map));
        break;
    case 1:
        memcpy(Map, Map_2, sizeof(Map));
        break;
    default:
        break;
    }
   //根据数字判断用switch语句判断该画什么
    for (int j = 0; j < 16; j++)
        for (int i = 0; i < 26; i++)
        {
            switch (Map[j][i])
            {
            case 0:     //草地
                painter.drawPixmap(i*40, j*40, 40, 40,QPixmap(":/image/grass.png"));
                break;
            case 1:     //地面
                painter.drawPixmap(i*40, j*40, 40, 40,QPixmap(":/image/road.png"));
                break;
            case 3:     //防御塔坑
                painter.drawPixmap(i*40, j*40, 80, 80,QPixmap(":/image/summoncircle.png"));
                //防御塔坑坐标插入到塔坑对象数组
                TowerTankVec.push_back(new TowerTank(i*40, j*40));
                break;
            case 5:
                painter.drawPixmap(i*40, j*40, 40, 40, QPixmap(":/image/road.png"));
                homecoor->x = i * 40, homecoor->y = j * 40;
                break;
            }
        }

    painter.drawPixmap(homecoor->x, homecoor->y, 80, 80,QPixmap(":/image/myhome.png"));//画出家
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

        //画出子弹
        for (auto bulli : defei->GetBulletVec())
            painter.drawPixmap(bulli->_coor.x, bulli->_coor.y, defei->GetBulletWidth(), defei->GetBulletHeight(),QPixmap(defei->GetBulletPath()));

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
    for (auto moni : MonsterVec)
        {
        //画出怪物
        if(moni->GetPoison()==false)
        {
            painter.drawPixmap(moni->GetX(), moni->GetY(), moni->GetWidth(), moni->GetHeight(), QPixmap(moni->GetImgPath()));
        }
        if(moni->GetPoison()==true)
            painter.drawPixmap(moni->GetX(), moni->GetY(), moni->GetWidth(), moni->GetHeight(), QPixmap(moni->GetPoiImgPath()));
    }

}

//画出升级按钮以及防御塔攻击范围圈圈
void MainWindow::DrawRangeAndUpgrade(QPainter& painter)
{
    for (auto defei : DefeTowerVec)
        if(defei->GetUpLeftX() == DisplayRangeX && defei->GetUpLeftY() == DisplayRangeY && DisplayRange)
        {   //画出防御塔攻击范围
            painter.setPen(QPen(Qt::white));  //设置颜色画出范围
            painter.drawEllipse(QPoint(DisplayRangeX + 40, DisplayRangeY + 40), defei->GetRange(), defei->GetRange());
            painter.drawPixmap(DisplayRangeX + 0, DisplayRangeY - 40, 90, 30, QPixmap(":/image/upgradebutton.png"));//画出升级按钮图片并设置大小和位置
        }
}
//画出防御塔拆除按钮
void MainWindow::DrawDestroyTower(QPainter &painter)
{
    for (auto defei : DefeTowerVec)
        if(defei->GetUpLeftX() == DisplayRangeX && defei->GetUpLeftY() == DisplayRangeY&&DisplayRange)
        {
            painter.drawEllipse(QPoint(DisplayRangeX + 40, DisplayRangeY + 40), defei->GetRange(), defei->GetRange());
            painter.drawPixmap(DisplayRangeX + 30, DisplayRangeY + 80, 40, 40, QPixmap(":/image/deletebutton.png"));//画出升级按钮图片并设置大小和位置
        }
}
//绘图事件
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);     //创建画家类

    DrawMapArr(painter);        //画出地图

    DrawDefenseTower(painter);  //画出防御塔和子弹

    DrawMonster(painter);       //画出怪物

    DrawRangeAndUpgrade(painter);//画出攻击范围和升级按钮

    DrawDestroyTower(painter);//画出拆塔按钮

    DrawSelectionBox(painter);  //画出选择框
}

//鼠标点击事件
void MainWindow::mousePressEvent(QMouseEvent *ev)
{    
    if (ev->button() != Qt::LeftButton)
        return;

    //判断是否点击了防御塔
    if (DisplayRange)
    {
        //假如鼠标点击区域落在以下坐标，那么是拆除
        if (ev->x()>=DisplayRangeX + 30&&ev->x()<=DisplayRangeX + 70&&ev->y()>=DisplayRangeY + 80&&ev->y()<=DisplayRangeY + 120)
        {
            //拆除防御塔
            for (auto defei = DefeTowerVec.begin();defei!=DefeTowerVec.end();defei++)
                if ((*defei)->GetUpLeftX() == DisplayRangeX && (*defei)->GetUpLeftY() == DisplayRangeY && DisplayRange)
                {
                    if (JudgeYourMoney(-100)) return;        //拆塔返100金币
                    (*defei)->SetAimsMonster(NULL);             //将防御塔目标怪兽设为空
                    DefeTowerVec.erase(defei);//删除塔
                    break;
                }
            SelBox->SetDisplay(false);      //取消显示新建防御塔框
            DisplayRange = false;           //取消显示自己
            update();
            return;
        }
        //假如鼠标点击区域落在以下坐标那么是升级防御塔
        if (ev->x()>=DisplayRangeX&&ev->x()<=DisplayRangeX + 90&&ev->y()>=DisplayRangeY - 40&&ev->y()<=DisplayRangeY-10)
        {
            //设置防御塔宽高，攻击力，微调坐标
            for (auto defei : DefeTowerVec)
                if (defei->GetUpLeftX() == DisplayRangeX && defei->GetUpLeftY() == DisplayRangeY && DisplayRange)
                {
                    if (JudgeYourMoney(200)) return;        //升级防御塔花费200

                    defei->SetAttack(defei->GetAttack() + 15);          //每次升级防御塔攻击力+15
                    defei->SetReduceSpeed(defei->GetReduceSpeed()+1);//减速效果增强
                    defei->SetPoisonHp(defei->GetPoisonHp()+2);//中毒效果增强
                    defei->SetWidthHeight(defei->GetWidth() + 12, defei->GetHeight() + 6);   //防御塔变大
                    defei->SetXY(defei->GetX() - 6, defei->GetY() - 3); //调整防御塔坐标
                    defei->SetAimsMonster(NULL);                        //将防御塔目标设为空
                    defei->SetRange() += 10;                            //防御塔的攻击范围扩大10
                    defei->SetBulletWidthHeight(defei->GetBulletWidth() + 5, defei->GetBulletHeight() + 5);          //子弹宽高重设
                    break;
                }

            SelBox->SetDisplay(false);      //取消显示新建防御塔框
            DisplayRange = false;           //取消显示自己
            update();
            return;
        }
    }



    //判断选择框四个子按钮的点击
    SubbutStr *ASubBut = SelBox->GetSelSubBut();
    for (int i = 0; i < 4; i++)
        if (ev->x()>=ASubBut[i].SubX&&ev->x()<=ASubBut[i].SubX+ASubBut[i].SubWidth&&ev->y()>=ASubBut[i].SubY&&ev->y()<=ASubBut[i].SubY+ASubBut[i].SubHeight&&SelBox->GetDisplay())
        {
            SelBox->SetDisplay(false);      //取消显示选择框
            //判断选择了哪一个
            switch (i)
            {
            case 0:
                if (JudgeYourMoney(200)) return;    //扣除金钱
                DefeTowerVec.push_back(new UltraManTaro(SelBox->GetX() + 110, SelBox->GetY() + 112, SelBox->GetX() + 95, SelBox->GetY() + 95, 70, 40));
                break;
            case 1:
                if (JudgeYourMoney(160)) return;
                DefeTowerVec.push_back(new UltraMan7 (SelBox->GetX() + 110, SelBox->GetY() + 112, SelBox->GetX() + 95, SelBox->GetY() + 95, 70, 40));
                break;
            case 2:
                if (JudgeYourMoney(240)) return;
                DefeTowerVec.push_back(new UltraManAce(SelBox->GetX() + 110, SelBox->GetY() + 112, SelBox->GetX() + 95, SelBox->GetY() + 95, 70, 40));
                break;
            case 3:
                if (JudgeYourMoney(200)) return;
                DefeTowerVec.push_back(new UltraManLeo(SelBox->GetX() + 110, SelBox->GetY() + 112, SelBox->GetX() + 95, SelBox->GetY() + 95, 32, 56));
                break;

            default:
                break;
            }
            update();
            return;
        }

    //遍历所有塔坑
    for (auto ATank : TowerTankVec)
        //判断点击塔坑
        if (ev->x()>=ATank->GetX()&&ev->x()<=ATank->GetX() + ATank->GetWidth() &&ev->y()>=ATank->GetY()&&ev->y()<=ATank->GetY()+ATank->GetHeight())
        {
            DisplayRange = false;               //降防御塔的升级选择显示关闭
            for (auto defei : DefeTowerVec)      //遍历数组判断防御塔坐标和点击坑坐标重合则返回
                if(defei->GetUpLeftX() == ATank->GetX() && defei->GetUpLeftY() == ATank->GetY())
                {
                    DisplayRangeX = defei->GetUpLeftX(), DisplayRangeY = defei->GetUpLeftY();   //记录要显示攻击范围的防御塔的坐标
                    DisplayRange = true;        //显示防御塔攻击范围
                    return;
                }
            SelBox->CheckTower(ATank->GetX(), ATank->GetY());  //选中防御塔，选择框显示
            update();

            return;
        }

    DisplayRange = false;           //取消显示防御塔攻击范围
    SelBox->SetDisplay(false);      //取消显示选择框

    update();
}


//析构函数
MainWindow::~MainWindow()
{

}
