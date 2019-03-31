#ifndef GUS_H
#define GUS_H

/*
 * 贪吃怪
 */

#include <QGraphicsItem>
#include <QPointF>
#include "alien.h"

class Gus:public Alien
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Gus(QObject* parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
public slots:
    void gameStop();
    void gameContinue();
private slots:
    void killFish();
};

#endif // GUS_H
