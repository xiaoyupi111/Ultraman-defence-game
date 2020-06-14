#include "defencetower.h"

int DefenceTower::GetX() const     //获取横坐标
{
    return _x;
}

int DefenceTower::GetY() const     //获取横坐标
{
    return _y;
}

int DefenceTower::GetWidth() const //获取宽
{
    return _w;
}

int DefenceTower::GetHeight() const //获取高
{
    return _h;
}

int DefenceTower::GetRotatAngle() const//获取旋转角度
{
    return ChangeAngle;
}

QString DefenceTower::GetDefImgPath() const   //获取防御塔图片路径
{
    return DefImgPath;
}

int DefenceTower::GetUpLeftX() const     //获取防御塔左上角原横坐标
{
    return UpLeftX;
}

int DefenceTower::GetUpLeftY() const     //获取防御塔左上角原纵坐标
{
    return UpLeftY;
}

void DefenceTower::SetChangeAngle(int ang)    //设置旋转角度
{
    ChangeAngle = ang;
}

int DefenceTower::GetRange() const           //获取防御塔射程
{
    return Range;
}

Monster* DefenceTower::GetAimsMonster() const //返回当前防御塔的目标怪物
{
    return targetmonster;
}

void DefenceTower::SetAimsMonster(Monster* monster)  //设置当前防御塔的目标怪物
{
    targetmonster = monster;
}

QString DefenceTower::GetBulletPath() const      //返回防御塔子弹图片路径
{
    return BullPath;
}

QVector<BulletStr*>& DefenceTower::GetBulletVec()//返回子弹数组
{
    return BulletVec;
}

void DefenceTower::InterBullet()     //新建子弹函数
{
    counter++;

    if(counter < 7 || !targetmonster)      //计数器且目标怪物不为空时直接返回
        return;

    //向子弹数组中插入子弹
    BulletStr *bull = new BulletStr(CoorStr(UpLeftX + 40, UpLeftY + 40));//插入子弹的位置

    bull->_coor.x = UpLeftX + 40, bull->_coor.y = UpLeftY + 40;

    //计算子弹的路径
    if((!(targetmonster->GetX() - bull->_coor.x)))   //除数为0时不创建子弹
    {
        delete bull;
        bull = NULL;
        goto L1;//直接去L1语句
    }

    bull->k = (targetmonster->GetY() - bull->_coor.y) / (targetmonster->GetX() - bull->_coor.x);//目标怪物和子弹的坐标差的商
    bull->b = targetmonster->GetY() - targetmonster->GetX() * bull->k;

    bull->_coor.x = UpLeftX + 40, bull->_coor.y = UpLeftY + 40;

    BulletVec.push_back(bull);              //将子弹插入到子弹数组当中

    if(targetmonster->GetX() <= UpLeftX + 40)     //确定子弹的移动方向
        bull->dirflag = true;//标识置为true
    L1://这是L1语句

    counter = 0;    //计数器重置为0
}

//子弹移动函数
void DefenceTower::BulletMove()
{
    for(auto bulli : BulletVec)//Bullet数组从头开始往后改变
    {
        const int speed = 25;              //设置子弹移动速度

        if(bulli->dirflag == true)
            bulli->_coor.x -= speed;        //根据移动方向标记判断每颗子弹的移动方向
        else
            bulli->_coor.x += speed;        //改变子弹横坐标

        bulli->_coor.y = bulli->k * bulli->_coor.x + bulli->b;    //改变子弹纵坐标
    }

    for(auto bullit = BulletVec.begin(); bullit != BulletVec.end(); bullit++)         //遍历删除超过当前窗口页面的子弹
        if((*bullit)->_coor.x > 1040 || (*bullit)->_coor.x < 0 || (*bullit)->_coor.y > 640 || (*bullit)->_coor.y < 0)
        {
            BulletVec.erase(bullit);
            break;
        }
}

int DefenceTower::GetBulletWidth() const //获取子弹的宽度
{
    return bullwidth;
}

int DefenceTower::GetBulletHeight() const//获取子弹的宽度
{
    return bullheight;
}
int DefenceTower::GetReduceSpeed()const//得到减速效果
{
    return _reducespeed;
}
void DefenceTower::SetReduceSpeed(int rspeed)//设置减速效果
{
    _reducespeed=rspeed;
}
int DefenceTower::GetAttack() const      //获取防御塔攻击力
{
    return attack;
}

void DefenceTower::SetAttack(int attack)       //设置防御塔攻击力
{
    this->attack = attack;
}

void DefenceTower::SetWidthHeight(int width, int height)  //设置防御塔宽高
{
    this->_w = width, this->_h= height;
}

void DefenceTower::SetXY(int x, int y)       //设置坐标
{
    this->_x = x, this->_y = y;
}

int& DefenceTower::SetRange()                //设置防御塔的攻击范围
{
    return Range;
}

void DefenceTower::SetBulletWidthHeight(int width, int height)         //设置子弹宽高
{
    bullwidth = width, bullheight = height;
}











