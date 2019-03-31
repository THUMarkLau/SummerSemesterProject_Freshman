#ifndef ALIEN_H
#define ALIEN_H

#include <QGraphicsItem>
#include <QString>
#include <QPixmap>
#include <QTimer>
#include <QObject>
#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include <QTime>
#include <QtMultimedia/QSound>
#include "guppi.h"

/*
 * 外星人类，可以产生红蓝两种外星人，并且可以作为其他外星人的基类
 */

class Alien:public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Alien(int alien_type, QObject *parent = 0);
    ~Alien();
    QRectF boundingRect() const; // 重载包围盒函数
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // 重载绘制函数
    void mousePressEvent(QGraphicsSceneMouseEvent *event); // 重载鼠标事件
    int type() const; // 返回其类型
    bool isAlive() const; // 返回其是否存活
public slots:
    void gameStop(); // 游戏暂停
    void gameContinue(); // 游戏继续
protected slots:
    void moveForward(); // 移动函数
    void killFish(); //
protected:
    void checkPos(); // 检查位置
    void checkLife(); // 检查是否死亡
signals:
    void dieInfo(Alien*); // 发出死亡信息
protected:
    QPixmap *pix_all; // 图片
    QPixmap pix_turn; // 某个方向的图片
    QPixmap pix_now; // 当前的图片
    QTimer *timer; // 计时器
    QSound *punch;// 击打的声音
    int lifetime; // 生命值
    int pix_index; // 迭代图片
    int m_type; // 种类
    bool alive;
    bool right; // 是否向右
    bool down; // 是否向下
};

#endif // ALIEN_H
