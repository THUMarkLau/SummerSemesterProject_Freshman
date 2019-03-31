#include "bigpredator.h"
#include "param.h"

BigPredator::BigPredator(int x, int y, QObject *parent):
    Fish(parent), pix_index(0), targetFish(nullptr)
{
    // TODO:设置坐标，加载图片
    setPos(x, y);
    pix->load(IMAGE_BIGPREDATOR);
}

QRectF BigPredator::boundingRect() const
{
    QPointF pos = scenePos();
    return QRectF(pos.x(), pos.y(), BIGPREDATOR_SIZE, BIGPREDATOR_SIZE);
}

void BigPredator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // TODO:根据参数得到当前帧的图片并打印
    pix_index %= 10;
    pix_now = pix->copy(BIGPREDATOR_SIZE * pix_index, BIGPREDATOR_SIZE*(count_right % 2),
                        BIGPREDATOR_SIZE, BIGPREDATOR_SIZE);
    QPointF pos = scenePos();
    painter->drawPixmap(pos.x(), pos.y(), BIGPREDATOR_SIZE, BIGPREDATOR_SIZE, pix_now);
    ++pix_index;
}

void BigPredator::checkPos(QPointF &pos)
{
    // TODO:检查自己的位置并清除食物
    if(!alive)
        return;
    eatFood();
    if(targetFish == nullptr)
    {
        if(pos.x() * 2 >= WIDTH_OF_WINDOW - BIGPREDATOR_SIZE)
            ++count_right;
        else if(pos.x() <= 0)
            ++count_right;
        if(pos.y() * 2 >= HEIGHT_OF_WINDOW - BIGPREDATOR_SIZE)
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
}

void BigPredator::die()
{
    // TODO:加载死亡的图片并且发出死亡的信号
    pix->load(IMAGE_DIE_BIGPREDATOR);
    alive = false;
    QTimer::singleShot(1000, this, SLOT(sendDeadSignal()));
}

void BigPredator::recieveFood(Predator *predator)
{
    // TODO:如果没有目标食物并且感到饥饿就设定目标食物
    if(targetFish == nullptr && full_value <= HUNGRY_VALUE)
    {
        targetFish = predator;
        connect(predator, SIGNAL(hasDead(Fish*)), this, SLOT(fishDelete(Fish*)));
    }
}

void BigPredator::resetFood()
{
    // TODO:重置目标食物为nullptr
    targetFish = nullptr;
}

void BigPredator::createMoney()
{
    // TODO:发出创造金钱的信号
    money_time = 0;
    QPointF pos = scenePos();
    emit moneyCreate(5, pos.x(), pos.y());
}

int BigPredator::type() const
{
    return TYPE_BIGPREDATOR;
}

void BigPredator::growing()
{
    // TODO:增加成长时和金钱积累时
    age += 1;
    money_time += 1;
    if(money_time >= CREATE_MONEY_TIME)
        createMoney();
}

void BigPredator::eatFood()
{
    // TODO:判断和食物之间的距离，距离近就吃掉食物
    if(targetFish == nullptr)
        return;
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

void BigPredator::fishDelete(Fish *fish)
{
    // TODO:如果被删除的鱼是目标食物，就将目标食物设置为空
    if(fish == targetFish)
    {
        targetFish = nullptr;
    }
}

void BigPredator::moveForward()
{
    // TODO:根据参数设置前进方向
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
                if(abs(full_value) <= 60)
                    pos.setX(pos.x() + 4 + static_cast<int>(abs(full_value) * 0.1));
                else
                    pos.setX(pos.x() + 10);
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
                if(abs(full_value) <= 60)
                    pos.setY(pos.y() + 4 + static_cast<int>(abs(full_value) * 0.08));
                else
                    pos.setY(pos.y() + 9);
            }
        }
        else
            pos.setY(pos.y() - 4);
    setPos(pos);
}
