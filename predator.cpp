#include "predator.h"
#include "param.h"
#include <QDebug>

Predator::Predator(int x, int y, QObject *parent):
    Fish(parent), pix_index(0), targetFish(nullptr)
{
    // TODO:设置位置，加载图片
    setPos(x, y);
    pix->load(IMAGE_PREDATOR);
    pix_now = pix->copy(0, 0, FISH_WIDTH * 10, FISH_HEIGHT * 2);
}

QRectF Predator::boundingRect() const
{
    //TODO:返回包围盒
    QPointF pos = scenePos();
    return  QRectF(pos.x(), pos.y(), FISH_WIDTH, FISH_HEIGHT);
}

void Predator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //TODO:根据参数得到当前帧的图片并且返回
    Q_UNUSED(option);
    Q_UNUSED(widget);
    pix_index %= 10;
    pix_now = pix->copy(0, 0, FISH_WIDTH * 10, FISH_HEIGHT * 2);
    QPixmap pix_ = pix_now.copy(pix_index * FISH_WIDTH, FISH_HEIGHT*(count_right % 2), FISH_WIDTH, FISH_HEIGHT);
    ++pix_index;
    QPointF pos = scenePos();
    painter->drawPixmap(pos.x(), pos.y(), FISH_WIDTH, FISH_HEIGHT, pix_);
}

void Predator::checkPos(QPointF &pos)
{
    //TODO: 检查自身位置，吃掉食物，并且发送自己的指针
    if(!alive)
        return;
    eatFood();
    emit selfInfo(this);
    if(targetFish == nullptr)
    {
        if(pos.x() * 2 >= WIDTH_OF_WINDOW - FISH_WIDTH)
            ++count_right;
        else if(pos.x() <= 0)
            ++count_right;
        if(pos.y() * 2 >= HEIGHT_OF_WINDOW - FISH_HEIGHT)
            ++count_down;
        else if(pos.y() * 2 <= HEIGHT_OF_BAR + 60)
            ++count_down;
    }
    else
    {
        if(pos.x() > targetFish->scenePos().x())
        {
            if(count_right % 2 == 0)
                ++count_right;
        }
        else if(pos.x() < targetFish->scenePos().x())
        {
            if(count_right % 2)
                ++count_right;
        }
        if(pos.y() > targetFish->scenePos().y())
        {
            if(count_down % 2 == 0)
                ++count_down;
        }
        else if(pos.y() < targetFish->scenePos().y())
        {
            if(count_down % 2)
                ++count_down;
        }

    }
    if(!hungry)
        pix->load(IMAGE_PREDATOR);
    else
        pix->load(IMAGE_HUNGRY_PREDATOR);
}

void Predator::die()
{
    // TODO:加载死亡图片，并且发送死亡信号
    pix->load(IMAGE_DIE_PREDATOR);
    alive = false;
    QTimer::singleShot(REFRESH_TIME * 10, this, SLOT(sendDeadSignal()));
}

void Predator::receiveFood(Guppi *guppi)
{
    // TODO:如果没有目标鱼，则设置目标鱼
    if(targetFish == nullptr && full_value <= HUNGRY_VALUE)
    {
        targetFish = guppi;
        connect(guppi, SIGNAL(hasDead(Fish*)), this, SLOT(fishDelete(Fish*)));
    }
}

void Predator::resetFood()
{
    // TODO:重置食物
    targetFish = nullptr;
}

void Predator::createMoney()
{
    // TODO:发送创造金钱的函数
    money_time = 0;
    QPointF pos = scenePos();
    emit moneyCreate(4, pos.x(), pos.y());
}

int Predator::type() const
{
    // TODO:返回其类型
    return TYPE_PREDATOR;
}

void Predator::growing()
{
    //TODO:增加成长时和金钱时
    age += 1;
    money_time += 1;
    if(money_time >= CREATE_MONEY_TIME)
        createMoney();
}

void Predator::eatFood()
{
    // TODO:计算自己和食物的距离，如果距离够近则吃掉食物
    if(targetFish == nullptr)
        return;
    if(targetFish->growStage() != GUPPI_GROW_STAGE_SMALL)
    {
        resetFood();
        return;
    }
    QPointF my_pos = scenePos(), food_pos = targetFish->scenePos();
    int gap_x = my_pos.x() - food_pos.x();
    int gap_y = my_pos.y() - food_pos.y();
    if(gap_x < 0 && gap_x > GAP_X_LOCK_RIGHT_FISH)
        hori_lock = true;
    else if(gap_x > 0 && gap_x < GAP_X_LOCK_LEFT_FISH)
        hori_lock = true;
    else
        hori_lock = false;
    if(abs(gap_y) < GAP_Y_LOCK_FISH)
        vert_lock = true;
    else
        vert_lock = false;
    if(hori_lock && vert_lock)
    {
        full_value = 130;
        targetFish->sendDeadSignal();
        targetFish = nullptr;
        hori_lock = false;
        vert_lock =false;
    }
}

void Predator::fishDelete(Fish *guppi)
{
    // TODO:如果被删除的食物是自己的目标食物，则重置食物
    if(guppi == targetFish)
    {
        targetFish = nullptr;
    }
}

void Predator::moveForward()
{
    // TODO:根据参数判断前进的方向
    QPointF pos = scenePos();
    checkPos(pos);
    if(!alive)
    {
        pos.setY(pos.y() + 5);
        return;
    }
    if(!hori_lock)
        if(count_right % 2 == 0)
        {
            if(!hungry || targetFish == nullptr)
                pos.setX(pos.x() + 4);
            else
            {
                if(abs(full_value) <= 50)
                    pos.setX(pos.x() + 4 + static_cast<int>(abs(full_value) * 0.1));
                else
                    pos.setX(pos.x() + 9);
            }
        }
        else
            pos.setX(pos.x() - 4);
    if(!vert_lock)
        if(count_down % 2 == 0)
        {
            if(!hungry || targetFish == nullptr)
                pos.setY(pos.y() + 4);
            else
            {
                if(abs(full_value) <= 50)
                    pos.setY(pos.y() + 4 + static_cast<int>(abs(full_value) * 0.08));
                else
                    pos.setY(pos.y() + 8);
            }
        }
        else
            pos.setY(pos.y() - 4);
    setPos(pos);
}
