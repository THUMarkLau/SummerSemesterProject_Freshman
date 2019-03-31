#ifndef GUPPIMUMMY_H
#define GUPPIMUMMY_H

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QPointF>
#include <QTimer>
#include <QPainter>
#include <QRectF>
#include "fish.h"

class GuppiMummy:public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    GuppiMummy(QObject *parent = 0);
    QRectF boundingRect() const; // 重载包围盒函数
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // 重载绘制函数
public slots:
    void gameStop(); // 游戏暂停
    void gameContinue(); // 游戏继续
private:
    QPixmap pix_all, pix_turn, pix_now; // 分别代表整张图、当前方向的图、当前帧数的图
    bool pregnant; // 是否怀孕
    bool right, down; // 是否向右、向下
    int pix_index; // 迭代当前帧数
    int pregnant_index; // 怀孕/生产迭代
    QTimer *timer; // 计时器
    QTimer *p_timer; // 怀孕计时器
private slots:
    void moveForward(); // 前进函数
    void checkPos(QPointF &); // 检查位置函数
    void bePregnant(); // 怀孕
signals:
    void createGuppi(int type, int x, int y); // 产生小鱼
};

#endif // GUPPIMUMMY_H
