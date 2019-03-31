#include "gus.h"
#include "param.h"
#include <QDebug>

Gus::Gus(QObject *parent):
    Alien(GUS_ALIEN_ID, parent)
{
}

void Gus::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    return;
}

void Gus::killFish()
{
    if(!alive)
    {
        qDebug() << alive;
        return;
    }
    QList<QGraphicsItem*> list = collidingItems();
    for(int index = 0; index < list.size(); ++index)
    {
        if(list[index]->type() == TYPE_FOOD)
        {
            Food *food = qgraphicsitem_cast<Food*>(list[index]);
            lifetime -= (food->Level()+1) * 20;
            food->beEaten();
        }
        else if(list[index]->type() == TYPE_GUPPI || list[index]->type() == TYPE_BREEDER
                || list[index]->type() == TYPE_PREDATOR || list[index]->type() == TYPE_BIGPREDATOR)
        {
            Fish *fish = qgraphicsitem_cast<Fish*>(list[index]);
            lifetime -= 40;
            fish->sendDeadSignal();
        }
    }
    checkLife();
}

void Gus::gameContinue()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(moveForward()));
    connect(timer, SIGNAL(timeout()), this, SLOT(killFish()));
}

void Gus::gameStop()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(moveForward()));
    disconnect(timer, SIGNAL(timeout()), this, SLOT(killFish()));
}

