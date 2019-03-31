#ifndef GUPPI_H
#define GUPPI_H


#include "fish.h"
#include "param.h"
#include <QRectF>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QPointF>
#include <QTime>

class Guppi: public Fish
{
    Q_OBJECT
public:
    Guppi(int x, int y, QObject *parent = 0);
    QRectF boundingRect() const; // 重载包围盒函数
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr); // 重载绘制函数
    int type() const; // 返回自己的类型
    int growStage() const; // 返回成长阶段
public slots:
    void recieveFoodPos(Food* food); // 接受食物的指针
    void resetFood(); // 重置食物
    void growing(); // 成长函数
signals:
    void posInfo(Guppi*); // 发送自己的指针
protected:
    void checkPos(QPointF &); // 检查自己的位置
    void die(); // 死亡函数
    void createMoney(); // 产生金钱函数
private:
    QPixmap pix_now; // 当前帧的图片
    int pix_index; // 迭代变量
    int randID; // 随机产生决定Guppi可否成为king
};

#endif // GUPPI_H
