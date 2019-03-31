#ifndef FOOD_H
#define FOOD_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <QWidget>
#include <QRectF>
#include <QPainter>
#include <QWidget>
#include <QStyleOptionGraphicsItem>
#include "param.h"

class Food:public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Food(int food_level, int x, int y);
    ~Food();
    QRectF boundingRect() const; // 重载包围盒函数
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // 重载绘制函数
    void beEaten(); // 被吃掉
    int Level() const; // 返回自己的等级
    void beLocked(); // 被鱼锁定
    bool isLocked(); // 返回是否被鱼锁定
    int type() const; // 返回自己的类型
public slots:
    void gameStop(); // 游戏暂停
    void gameContinue(); //游戏继续
private:
    bool locked; // 是否被鱼锁定
    QPixmap *pix_all, pix_now; // 所有图片和当前帧的图片
    int level; // 食物的等级
    int pix_index; // 用于迭代图片
    QTimer *timer; // 计时器
    void checkPos(); // 检查位置是否正确
    bool bottom; // 是否到达了底部
private slots:
    void moveForward(); // 前进函数
    void deleteSelf(); // 删除自身
    void sendPos(); // 发送自身的位置
signals:
    void toBeDeleted(Food*); // 删除自身
    void position(Food*); // 发送自身位置和ID
    void willBeDeleted(); // 发送给鱼，告知将要被删除
};

#endif // FOOD_H
