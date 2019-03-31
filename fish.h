#ifndef FISH_H
#define FISH_H


/*
 * Fish类作为所有鱼的基类，包括了所有鱼都含有的基本属性
*/

#include <QGraphicsItem>
#include <QString>
#include <QPixmap>
#include <QTimer>
#include <QGraphicsScene>
#include <QWidget>
#include <QPointF>
#include <QtMultimedia/QSound>
#include "food.h"
#include "money.h"

class Fish: public QObject, public QGraphicsItem
{

    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Fish(QObject *parent = 0);
    ~Fish();
protected:
    QString name; //鱼的种类
    QPixmap *pix; // 鱼的外观
    QPixmap *pix_now; // 鱼当前对应帧数的外表
    int money; // 鱼单位时间内产生的收益
    int age; // 鱼的年龄
    int full_value;// 鱼的饥饿程度
    bool hungry; // 鱼是否饥饿
    bool alive; // 鱼是否活着
    int grow_stage; //鱼的成长阶段
    QTimer *timer; // 计时器
    int count_down, count_right; // 记录鱼的方向
    Food* targetFood; // 目标食物的指针
    bool hori_lock, vert_lock; // 锁定水平和竖直方向的位移
    int money_time; // 记录产生金钱的间隔
    QSound *eat; // 吃食物的声音
    virtual void createMoney() = 0; //产生金钱的函数
    int move_index; // 迭代移动
public slots:
    virtual void growing() = 0; // 生长函数
    void feed(int feed_value); // 被喂食函数
    void becomeHungry(); // 渐渐变饿
    virtual void moveForward(); // 前进函数
    void sendDeadSignal();
    void gameStop(); // 游戏暂停
    void gameContinue(); // 游戏继续

signals:
    void hasDead(Fish*); // 发出自己死亡的信号
    void moneyCreate(int level, int x, int y); // 创造金钱的信号
protected:
    virtual void checkPos(QPointF&) = 0;
    virtual void die() = 0; // 死亡
    virtual void eatFood(); // 吃食物
};

#endif // FISH_H
