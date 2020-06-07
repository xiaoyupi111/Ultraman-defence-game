#ifndef START_H
#define START_H

#include <QWidget>
//开始界面
namespace Ui
{
class StartPage;
}

class StartPage : public QWidget
{
//    Q_OBJECT

public:
    explicit StartPage(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);//绘制背景地图
    ~StartPage();

private:
    Ui::StartPage *ui;
};

#endif // START_H
