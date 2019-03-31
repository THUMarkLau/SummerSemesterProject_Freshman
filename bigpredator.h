#ifndef BIGPREDATOR_H
#define BIGPREDATOR_H

#include "fish.h"
#include <QPointF>
#include <QRectF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include "predator.h"
#include <QList>

/*
 * 大食人鱼
 */

class BigPredator:public Fish
{
    Q_OBJECT
public:
    BigPredator(int x, int y, QObject *parent = 0);
    QRectF boundingRect() const; // 重载包围盒函数
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // 重载绘制函数
    int type() const; // 返回其类型
public slots:
    void recieveFood(Predator*); // 接受Predator的指针
    void resetFood(); // Predator消失，重置
    void growing(); // 成长函数
    void fishDelete(Fish*); // 目标鱼被其他鱼吃了
    void moveForward(); // 移动函数
private:
    void checkPos(QPointF &); // 检查位置
    void die(); // 死亡函数
    void createMoney(); // 产生金钱
    void eatFood(); // 吃食物
private:
    int pix_index; // 迭代每一帧图片
    QPixmap pix_now; // 当前帧的图片
    Predator *targetFish; // 目标鱼的指针
};

#endif // BIGPREDATOR_H
