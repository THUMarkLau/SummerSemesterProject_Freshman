#include "myscene.h"
#include <QDebug>

MyScene::MyScene(QObject* parent):QGraphicsScene(parent)
{
}

void MyScene::removeSlotItem(Fish* item)
{
    // TODO:删除无效的物品
    removeItem(item);
    delete item;
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // TODO:将鼠标点击事件传递下去
    QGraphicsScene::mousePressEvent(event);

}
