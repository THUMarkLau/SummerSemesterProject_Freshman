#ifndef MONEY_H
#define MONEY_H


/*
 * 鱼儿产生的金钱
 */

#include <QGraphicsItem>
#include <QObject>
#include <QRectF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QPixmap>
#include <QTimer>
#include <QPointF>
#include <QMouseEvent>
#include <QGraphicsSceneEvent>
#include <QtMultimedia/QSound>
class Money:public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Money(int init_level, int x, int y, QObject *parent = 0);
    ~Money();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //重载绘制函数
    QRectF boundingRect() const; // 重载包围盒函数
    void mousePressEvent(QGraphicsSceneMouseEvent *event); // 重载鼠标事件
    void getBySnail(); // 被蜗牛接住
    int type() const; // 返回其类型
    bool isAlive() const; // 返回其是否有效
public slots:
    void gameStop(); // 游戏暂停
    void gameContinue(); // 游戏继续
    void moveForward(); // 移动函数
    void emitDelete(); // 发出被删除的信号
    void setAlive(bool); // 设置是否有效
private:
    // 数据
    bool alive; // 金钱是否有效
    int level; // 金钱的等级
    int value; // 金钱的价格
    int pix_index; // 迭代图像帧数
    bool bottom; // 是否到达底部
    QPixmap  pix; // 图像
    QPixmap pix_now; // 当前帧的图像
    QTimer *timer; // 计时器
    QSound *click; // 被点击的声音
private:
    // 函数
    void checkPos(); // 检查位置
signals:
    void getClicked(int, Money*); // 被点击
    void deleteSelf(Money*); // 删除自身
    void posInfo(Money*); // 广播自己的x坐标
};

#endif // MONEY_H
