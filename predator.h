#ifndef PREDATOR_H
#define PREDATOR_H

#include "fish.h"
#include <QPointF>
#include <QRectF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include "guppi.h"
#include <QList>

class Predator:public Fish
{
    Q_OBJECT
public:
    Predator(int x, int y, QObject *parent = 0);
    QRectF boundingRect() const; // 重载包围盒函数
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // 重载绘制函数
    int type() const; // 返回其类型
public slots:
    void receiveFood(Guppi*);
    void resetFood();
    void growing();
    void fishDelete(Fish*); // 目标鱼被别的鱼吃掉了
    void moveForward();
signals:
    void selfInfo(Predator*); // 散布自身的消息
private:
    void checkPos(QPointF &);
    void die();
    void createMoney();
    void eatFood();
private:
    int pix_index;
    QPixmap pix_now;
    Guppi *targetFish;
};

#endif // PREDATOR_H
