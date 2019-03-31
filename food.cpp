#include "food.h"
#include <QDebug>

Food::Food(int food_level, int x, int y):
    pix_all(new QPixmap), level(food_level), timer(new QTimer),
    pix_index(0), bottom(false), locked(false)
{
    // TODO:设置位置，加载图片，初始化计时器
    setPos(x, y);
    pix_all->load(IMAGE_FOOD);
    timer->start(REFRESH_TIME);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(moveForward()));
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(sendPos()));
}

QRectF Food::boundingRect() const
{
    // TODO:返回包围盒
    QPointF pos = scenePos();
    return QRectF(pos.x(), pos.y(),  FOOD_WIDTH, FOOD_HEIGHT);
}

void Food::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    // TODO:根据参数得到当前帧的图片并绘制
    pix_index %= 10;
    pix_now = pix_all->copy(pix_index * FOOD_WIDTH, level * FOOD_HEIGHT, FOOD_WIDTH, FOOD_HEIGHT);
    ++pix_index;
    QPointF pos = scenePos();
    painter->drawPixmap(pos.x(), pos.y(), FOOD_WIDTH, FOOD_HEIGHT, pix_now);
}

void Food::moveForward()
{
    // TODO:如果食物没有到达底部就继续向下移动
    checkPos();
    QPointF pos = scenePos();
    if(!bottom)
    {
        setPos(pos.x(), pos.y() + 2);
    }
}

void Food::gameStop()
{
    // TODO:断开计时器和移动函数的链接
    QObject::disconnect(timer, SIGNAL(timeout()), this, SLOT(moveForward()));
}

void Food::gameContinue()
{
    // TODO:链接计时器和移动函数
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(moveForward()));
}

void Food::checkPos()
{
    // TODO:检查食物是否到达底部
    QPointF pos = scenePos();
    if(pos.y() * 2 >= HEIGHT_OF_WINDOW - FOOD_HEIGHT - 30)
    {
        if(!bottom)
        {
            QTimer::singleShot(1000, this, SLOT(deleteSelf()));
        }
        bottom = true;
    }
}

void Food::deleteSelf()
{
    // TODO:发出自己将被删除的信息
    emit willBeDeleted();
    emit toBeDeleted(this);
}

void Food::sendPos()
{
    // TODO:发出自己的指针
    emit position(this);
}

void Food::beEaten()
{
    // TODO:调用删除自己的函数
    deleteSelf();
}

int Food::Level() const
{
    // TODO:返回自己的等级
    return level;
}

void Food::beLocked()
{
    // TODO:将锁定变量设置为true
    locked = true;
}

bool Food::isLocked()
{
    // TODO:返回是否被锁定
    return locked;
}

int Food::type() const
{
    // TODO:返回自己的类型
    return TYPE_FOOD;
}

Food::~Food()
{
    delete pix_all;
    delete timer;
}
