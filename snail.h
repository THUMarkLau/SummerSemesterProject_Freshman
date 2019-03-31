#ifndef SNAIL_H
#define SNAIL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPointF>
#include <QRectF>
#include <QPixmap>
#include <QTimer>
#include <QPainter>
#include <QList>
#include "money.h"

class Snail:public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Snail(QObject *parent = 0);
    ~Snail();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
    void alienComing(bool); // 告知蜗牛外星人即将到来
public slots:
    void gameStop(); // 游戏暂停
    void gameContinue(); // 游戏继续
    void recievePos(Money* mon); // 接收金钱的指针
    void moneyDelete(Money*); // 钱消失了
private:
    QPixmap pix_move, pix_hide; // 分别是蜗牛行走和躲藏时的图片
    QPixmap pix_turn, pix_now; // 当前方向和当前帧的图像
    QTimer *timer; // 计时器
    int pix_index; // 迭代图像
    int hide_pix_index; // 迭代躲藏图像
    int target_x; // 目标位置
    bool hide; // 是否躲藏
    bool right; // 是否向右走
    bool hori_lock; //水平移动锁定
    Money* money; // 目标金钱
private slots:
    void moveForward(); // 移动函数
    void checkPos(); // 检查位置
    void getMoney(); // 得到金钱的函数
};

#endif // SNAIL_H
