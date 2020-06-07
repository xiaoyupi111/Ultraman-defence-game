#include "start.h"
#include "ui_startpage.h"
#include "mainwindow.h"
#include <QSound>


StartPage::StartPage(QWidget *parent) : QWidget(parent),ui(new Ui::StartPage)
{
    ui->setupUi(this);

    setWindowTitle("开始界面");

    QSound *sound = new QSound(":/media/startbgm.wav");//播放开始背景音乐
    sound->play();
    sound->setLoops(-1);//设置循环次数

    //补充：qmediaplay不知道为什么不可以实现，查询后下载了插件也没办法，Qsound不能设置音量大小。

    //客户端connect函数，发起连接请求,进行画面切换
    connect(ui->pushButton, &QPushButton::clicked, this,[=]()
    {
        //点击按钮进入关卡
        MainWindow *mainwindow = new MainWindow();
        mainwindow->show(); //显示游戏界面
        this->close();//关闭开始界面
        sound->stop();//停止播放开头背景音乐
    });
}

void StartPage::paintEvent(QPaintEvent *)//绘制背景
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/image/开始界面.jpg"));
}

StartPage::~StartPage()//析构
{
    delete ui;
}
