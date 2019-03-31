#include "money.h"
#include "param.h"
#include <QDebug>

Money::Money(int init_level, int x, int y, QObject* parent):
    level(init_level), QObject(parent), timer(new QTimer),
    pix_index(0), bottom(false), click(new QSound(SOUND_MONEY)),
    alive(true)
{
    // TODO:设置位置，加载图片，并且根据不同level的金钱设置不同的价格
    setPos(x, y);
    pix.load(IMAGE_MONEY);
    switch(level)
    {
    case 0:
    {
        value = MONEY_VALUE_ONE;
        break;
    }
    case 1:
    {
        value = MONEY_VALUE_TWO;
        break;
    }
    case 2:
    {
        value = MONEY_VALUE_THREE;
        break;
    }
    case 3:
    {
        value = MONEY_VALUE_FOUR;
        break;
    }
    case 4:
    {
        value = MONEY_VALUE_FIVE;
        break;
    }
    case 5:
    {
        value = MONEY_VALUE_SIX;
        break;
    }
    }
    pix = pix.copy(0, (level - 1) * 72, MONEY_SIZE * 10, MONEY_SIZE);
    timer->start(REFRESH_TIME);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveForward()));
}

QRectF Money::boundingRect() const
{
    // TODO:返回包围盒
   QPointF pos = scenePos();
    return QRectF(pos.x(), pos.y(),MONEY_SIZE, MONEY_SIZE);
}

void Money::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // TODO:根据参数得到当前帧的图片并且绘制
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPointF pos = scenePos();
    pix_index %= 10;
    pix_now = pix.copy(pix_index * MONEY_SIZE, 0, MONEY_SIZE, MONEY_SIZE);
    painter->drawPixmap(pos.x(), pos.y(), MONEY_SIZE, MONEY_SIZE, pix_now);
    ++pix_index;
}

void Money::checkPos()
{
    // TODO:检查位置
    QPointF pos = scenePos();
    emit posInfo(this);
    if(pos.y() * 2 >= HEIGHT_OF_WINDOW - MONEY_SIZE - 30 && !bottom)
    {
        bottom = true;
        QTimer::singleShot(1000, this, SLOT(emitDelete()));
    }
}

void Money::moveForward()
{
    // TODO:如果没有到达底部则继续向下坠落
    QPointF pos = scenePos();
    checkPos();
    if(!bottom)
    {
        setPos(pos.x(), pos.y() + 3);
    }

    prepareGeometryChange();
}

void Money::gameStop()
{
    // TODO:断开计时器和函数的链接
    disconnect(timer, SIGNAL(timeout()), this, SLOT(moveForward()));
}

void Money::gameContinue()
{
    // TODO:链接计时器和函数
    connect(timer, SIGNAL(timeout()), this, SLOT(moveForward()));
}

void Money::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // TODO:如果被点击了则被收取
    if(event->button() == Qt::LeftButton)
    {
        click->play();
        emit getClicked(value, this);
        alive = false;
    }
}

void Money::emitDelete()
{
    // TODO:将状态改为无效
    alive = false;
}

int Money::type() const
{
    // TODO:返回其类型值
    return TYPE_MONEY;
}

void Money::getBySnail()
{
    // TODO:被蜗牛接到，发出被点击的信号
    emit getClicked(value, this);
}

Money::~Money()
{
    delete timer;
}

bool Money::isAlive() const
{
    // TODO:返回其是否有效
    return alive;
}

void Money::setAlive(bool a)
{
    // TODO:设置其是否有效
    alive = a;
}
