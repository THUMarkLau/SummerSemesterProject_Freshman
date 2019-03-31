#include "guppi.h"
#include "math.h"
#include <QPainter>
#include <QDebug>
#include <QPointF>

Guppi::Guppi(int x, int y, QObject *parent):
    Fish(parent), pix_index(0)
{
    // TODO:产生随机坐标，加载图片
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    randID = qrand();
    setPos(x, y);
    pix->load(IMAGE_GUPPI);
    pix_now = pix->copy(pix_index * 80, 0, FISH_WIDTH, FISH_HEIGHT * 2);
}

QRectF Guppi::boundingRect() const
{
    // TODO:返回包围盒
    QPointF pos = scenePos();
    return QRectF(pos.x(), pos.y(),  FISH_WIDTH, FISH_HEIGHT);
}

void Guppi::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // TODO:根据参数得到当前帧的图片并且打印
    pix_index %= 10;
    pix_now = pix->copy(0, grow_stage*2*FISH_HEIGHT, FISH_WIDTH * 10, FISH_HEIGHT * 2);
    QPixmap pix_ = pix_now.copy(pix_index * FISH_WIDTH, FISH_HEIGHT*(count_right%2),
                                FISH_WIDTH,FISH_HEIGHT);
    ++pix_index;
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPointF pos = scenePos();
    painter->drawPixmap(pos.x(), pos.y(), FISH_WIDTH, FISH_HEIGHT, pix_);
}

void Guppi::checkPos(QPointF &pos)
{
    // TODO:判断自身位置，并调用吃食函数
    if(!alive)
        return;
    this->eatFood();
    if(targetFood == nullptr)
    {
        if(pos.x() * 2 >= WIDTH_OF_WINDOW - FISH_WIDTH || pos.x() <= 0)
            ++count_right;
        if(pos.y() * 2 >= HEIGHT_OF_WINDOW - FISH_HEIGHT || (pos.y() * 2) <= HEIGHT_OF_BAR + 60)
            ++count_down;
    }
    else
    {
        if(pos.x() > targetFood->scenePos().x())
        {
            if(count_right % 2 == 0)
                ++count_right;
        }
        else if(pos.x() < targetFood->scenePos().x())
        {
            if(count_right % 2)
                ++count_right;
        }
        if(pos.y() > targetFood->scenePos().y())
        {
            if(count_down % 2 == 0)
                ++count_down;
        }
        else if(pos.y() < targetFood->scenePos().y())
        {
            if(count_down % 2)
                ++count_down;
        }

    }
    if(!hungry)
    {
        pix->load(IMAGE_GUPPI);
    }
    else
    {
        pix->load(IMAGE_GUPPI_HUNGRY);
    }
}

void Guppi::die()
{
    // TODO:加载死亡图片，发出死亡信号
    pix->load(IMAGE_GUPPI_DIE);
    alive = false;
    QTimer::singleShot(1000, this, SLOT(sendDeadSignal()));
}

void Guppi::recieveFoodPos(Food *food)
{
    // TODO:如果没有目标食物，则设置目标食物
    if(targetFood == nullptr && !food->isLocked() && full_value <= GET_FOOD_VALUE)
    {
        targetFood = food;
        food->beLocked();
        QObject::connect(food, SIGNAL(willBeDeleted()), this, SLOT(resetFood()));
    }
}

void Guppi::resetFood()
{
    // TODO:重置食物
    targetFood = nullptr;
}

void Guppi::createMoney()
{
    // TODO:发出创造金钱的信号
    money_time = 0;
    if(grow_stage == GUPPI_GROW_STAGE_SMALL)
        return;
    QPointF pos = scenePos();
    emit moneyCreate(grow_stage, pos.x(), pos.y());
}

int Guppi::type() const
{
    // TODO:返回自己的类型
    return TYPE_GUPPI;
}

void Guppi::growing()
{
    // TODO:增加成长时，并且根据成长时判断成长阶段
    age += 1;
    money_time += 1;
    if(money_time > CREATE_MONEY_TIME)
        createMoney();
    if(age > GUPPI_GROW_TO_KING && randID % 2 == 0)
        grow_stage = GUPPI_GROW_STAGE_KING;
    else if(age > GUPPI_GROW_TO_BIG)
        grow_stage = GUPPI_GROW_STAGE_BIG;
    else if(age > GUPPI_GROW_TO_MIDDLE)
        grow_stage = GUPPI_GROW_STAGE_MIDDLE;

    if(grow_stage == GUPPI_GROW_STAGE_SMALL)
        emit posInfo(this);
}

int Guppi::growStage() const
{
    // TODO:返回自己的成长阶段
    return grow_stage;
}
