#include "guppimummy.h"
#include "param.h"
#include <QDebug>

GuppiMummy::GuppiMummy(QObject *parent):
    QObject(parent), pix_index(0), pregnant(false),
    timer(new QTimer), right(true), down(true),
    p_timer(new QTimer), pregnant_index(0)
{
    // TODO: 加载图片并且设置位置，初始化计时器
    pix_all.load(IMAGE_GUPPI_MUMMY);
    setPos(100, 100);
    pix_turn = pix_all.copy(0, 0, GUPPI_MUMMY_SIZE * 10, GUPPI_MUMMY_SIZE);
    timer->start(REFRESH_TIME);
    p_timer->start(PREGNANT_TIME);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveForward()));
}

QRectF GuppiMummy::boundingRect() const
{
    // TODO:返回包围盒
    QPointF pos = scenePos();
    return QRectF(pos.x(), pos.y(), GUPPI_MUMMY_SIZE, GUPPI_MUMMY_SIZE);
}

void GuppiMummy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // TODO:根据参数得到当前帧的图片并且打印
    Q_UNUSED(widget);
    Q_UNUSED(option);
    QPointF pos = scenePos();
    if(right)
    {
        pix_turn = pix_all.copy(0, 0, GUPPI_MUMMY_SIZE * 10, GUPPI_MUMMY_SIZE);
    }
    else
    {
        pix_turn = pix_all.copy(0, GUPPI_MUMMY_SIZE, GUPPI_MUMMY_SIZE * 10, GUPPI_MUMMY_SIZE);
    }
    pix_index %= 10;
    pix_now = pix_turn.copy(pix_index * GUPPI_MUMMY_SIZE, 0, GUPPI_MUMMY_SIZE, GUPPI_MUMMY_SIZE);
    painter->drawPixmap(pos.x(), pos.y(), GUPPI_MUMMY_SIZE, GUPPI_MUMMY_SIZE, pix_now);
    ++pix_index;
}

void GuppiMummy::gameStop()
{
    // TODO:接触计时器和函数的链接
    disconnect(timer, SIGNAL(timeout()), this, SLOT(moveForward()));
    disconnect(p_timer, SIGNAL(timeout()), this, SLOT(bePregnant()));
}

void GuppiMummy::gameContinue()
{
    // TODO:链接计时器和函数
    connect(timer, SIGNAL(timeout()), this, SLOT(moveForward()));
    connect(p_timer, SIGNAL(timeout()), this, SLOT(bePregnant()));
}

void GuppiMummy::moveForward()
{
    // TODO:根据参数前进
    QPointF pos = scenePos();
    checkPos(pos);
    if(right)
        pos.setX(pos.x() + 2);
    else
        pos.setX(pos.x() - 2);
    if(down)
        pos.setY(pos.y() + 2);
    else
        pos.setY(pos.y() - 2);
    setPos(pos);
}

void GuppiMummy::checkPos(QPointF &pos)
{
    //TODO: 检查自己的位置
    if(pos.x() * 2 >= WIDTH_OF_WINDOW - GUPPI_MUMMY_SIZE)
        right = false;
    else if(pos.x() <= 0)
        right = true;
    if(pos.y() * 2 <= HEIGHT_OF_BAR + 30)
        down = true;
    else if(pos.y() * 2 >= HEIGHT_OF_WINDOW - GUPPI_MUMMY_SIZE)
        down = false;
}

void GuppiMummy::bePregnant()
{
    // TODO:根据怀孕迭代判断状态，并加载对应的图片
    ++pregnant_index;
    if(pregnant_index % 2 == 1)
    {
        pregnant = true;
        pix_all.load(IMAGE_GUPPI_MUMMY_P);
    }
    else
    {
        pregnant = false;
        pix_all.load(IMAGE_GUPPI_MUMMY);
        QPointF pos = scenePos();
        emit createGuppi(TYPE_GUPPI, pos.x(), pos.y());
    }
}

