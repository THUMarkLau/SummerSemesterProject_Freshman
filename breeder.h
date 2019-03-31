#ifndef BREEDER_H
#define BREEDER_H

#include "fish.h"
#include <QRectF>
#include <QPainter>
#include <QPointF>
#include <QStyleOptionGraphicsItem>
#include <QPixmap>
#include <QTimer>
#include "food.h"


class Breeder:public Fish
{
    Q_OBJECT
public:
    Breeder(int x, int y, QObject* parent = 0);
    ~Breeder();
    QRectF boundingRect() const; // 重载包围盒函数
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);// 重载绘制函数
    int type() const; // 返回其类型
public slots:
    void recieveFood(Food*); // 接受食物的指针
    void resetFood(); // 食物被其他鱼吃了，重置
    void growing(); // 成长函数
signals:
    void createFish(int type, int x, int y); // 产生小鱼的信号
protected:
    void checkPos(QPointF &); // 检查位置
    void die(); // 死亡函数
    void createMoney(); // 产生金钱
private:
    QPixmap pix_now; // 当前帧的图片
    QTimer *c_timer; // 记录创造小鱼的计时器
    int pix_index, c_count; // 迭代图片，记录产生小鱼的时间
};

#endif // BREEDER_H
