#include "snail.h"
#include "param.h"
#include <QDebug>

Snail::Snail(QObject *parent):
    QObject(parent), timer(new QTimer), pix_index(0),
    hide(false), right(true), money(nullptr),
    target_x(-1), hori_lock(false), hide_pix_index(0)
{
    // TODO:设立位置，加载图片
    pix_move.load(IMAGE_SNAIL);
    pix_hide.load(IMAGE_SNAIL_HIDE);
    timer->start(REFRESH_TIME);
    setPos(0, 320);
}

QRectF Snail::boundingRect() const
{
    //TODO:返回包围盒
    QPointF pos = scenePos();
    return QRectF(pos.x(), pos.y(), SNAIL_SIZE, SNAIL_SIZE);
}

void Snail::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //TODO:根据参数找到当前帧的图片，并且打印
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(!hide)
    {
        pix_index %= 10;
        if(right)
        {
            pix_turn = pix_move.copy(0, 0, SNAIL_SIZE * 10, SNAIL_SIZE);
        }
        else
        {
            pix_turn = pix_move.copy(0, SNAIL_SIZE, SNAIL_SIZE * 10, SNAIL_SIZE);
        }
        pix_now = pix_turn.copy(pix_index * SNAIL_SIZE, 0, SNAIL_SIZE, SNAIL_SIZE);
        QPointF pos = scenePos();
        painter->drawPixmap(pos.x(), pos.y(), SNAIL_SIZE, SNAIL_SIZE, pix_now);
        ++pix_index;
    }
    else if(hide_pix_index < 10)
    {
        if(right)
        {
            pix_turn = pix_hide.copy(0, 0, SNAIL_SIZE * 10, SNAIL_SIZE);
        }
        else
        {
            pix_turn = pix_hide.copy(0, SNAIL_SIZE, SNAIL_SIZE*10, SNAIL_SIZE);
        }
        pix_now = pix_turn.copy(hide_pix_index * SNAIL_SIZE, 0, SNAIL_SIZE, SNAIL_SIZE);
        QPointF pos = scenePos();
        painter->drawPixmap(pos.x(), pos.y(), SNAIL_SIZE, SNAIL_SIZE, pix_now);
        ++hide_pix_index;
    }
    else
    {
        pix_hide.load(IMAGE_SNAIL_HIDE);
        pix_now = pix_hide.copy(9 * SNAIL_SIZE, SNAIL_SIZE, SNAIL_SIZE, SNAIL_SIZE);
        QPointF pos = scenePos();
        painter->drawPixmap(pos.x(), pos.y(), SNAIL_SIZE, SNAIL_SIZE, pix_now);
    }
}

void Snail::moveForward()
{
    //TODO:根据参数判断自己前进的方向
    checkPos();
    QPointF pos = scenePos();
    if(hori_lock || hide)
        return;
    if(money == nullptr)
    {
        if(right)
            pos.setX(pos.x() + 3);
        else
            pos.setX(pos.x() - 3);
    }
    else
    {
        if(pos.x() > target_x)
        {
            pos.setX(pos.x() - 3);
            right = false;
        }
        else if (pos.x() < target_x)
        {
            pos.setX(pos.x() + 3);
            right = true;
        }
    }
    setPos(pos);
}

void Snail::checkPos()
{
    //TODO:判断自己的位置
    QPointF pos = scenePos();
    getMoney();
    if(money == nullptr)
    {
        hori_lock = false;
        if(pos.x() * 2 >= WIDTH_OF_WINDOW - SNAIL_SIZE)
        {
            right = false;
        }
        else if(pos.x() <= 0)
        {
            right = true;
        }
    }
    else
    {
        if(abs(pos.x()*2 - money->scenePos().x()*2) <= 5)
            hori_lock = true;
        else
            hori_lock = false;
    }
}

void Snail::gameStop()
{
    //TODO:切断计时器和前进函数的链接
    disconnect(timer, SIGNAL(timeout()), this, SLOT(moveForward()));
}

void Snail::gameContinue()
{
    //TODO:链接计时器和前进函数
    connect(timer, SIGNAL(timeout()), this, SLOT(moveForward()));
}

void Snail::recievePos(Money *mon)
{
    //TODO:接受金钱的指针，如果没有目标金钱，则设立目标金钱
    if(money != nullptr)
        return;
    money = mon;
    target_x = money->scenePos().x();
}

void Snail::getMoney()
{
    //TODO:如果和自己碰撞的物体是金钱，则将其收获
    QList<QGraphicsItem*> list = collidingItems();
    for(int index = 0; index < list.size(); ++index)
    {
        if(list[index]->type() == TYPE_MONEY)
        {
            Money* money = qgraphicsitem_cast<Money*>(list[index]);
            money->setAlive(false);
            money = nullptr;
        }
    }
}

void Snail::moneyDelete(Money* mon)
{
    // TODO:如果被删除的金钱是自己的目标金钱，则将其删除
    if(mon == money)
    {
        money = nullptr;
        target_x = -1;
    }
}

int Snail::type() const
{
    //TODO:返回其类型值
    return TYPE_SNAIL;
}

Snail::~Snail()
{
    delete timer;
}

void Snail::alienComing(bool c)
{
    //TODO:切换自己躲藏/前进的状态
    if(c)
    {
        hide = true;
        hide_pix_index = 0;
    }
    else
    {
        hide = false;
        hide_pix_index = 0;
    }
}
