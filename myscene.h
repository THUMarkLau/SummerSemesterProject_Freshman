#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QObject>
#include "fish.h"

class MyScene:public QGraphicsScene
{
    Q_OBJECT
public:
    MyScene(QObject *parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event); // 重载鼠标点击函数
public slots:
    void removeSlotItem(Fish* fish); // 移除死亡的鱼
};

#endif // MYSCENE_H
