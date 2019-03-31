#include "breeder.h"

Breeder::Breeder(int x, int y, QObject *parent):
    Fish(parent), pix_index(0), c_timer(new QTimer),
    c_count(0)
{
    // TODO:初始化位置、计时器，加载图片
    setPos(x, y);
    c_timer->start(REFRESH_TIME);
    pix->load(IMAGE_BREEDER);
    pix_now = pix->copy(0, 0, FISH_WIDTH * 10, FISH_HEIGHT * 2);

    connect(c_timer, SIGNAL(timeout()), this, SLOT(growing()));
}

QRectF Breeder::boundingRect() const
{
    QPointF pos = scenePos();
    return QRectF(pos.x(), pos.y(), FISH_WIDTH, FISH_HEIGHT);
}

void Breeder::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    // TODO:根据参数得到当前帧的图片并且绘制
    pix_index %= 10;
    QPixmap pix_ = pix_now.copy(FISH_WIDTH * pix_index, FISH_HEIGHT*(count_right % 2), FISH_WIDTH, FISH_HEIGHT);
    ++pix_index;
    QPointF pos = scenePos();
    painter->drawPixmap(pos.x(), pos.y(), FISH_WIDTH, FISH_HEIGHT, pix_);
}

void Breeder::checkPos(QPointF &pos)
{
    //TODO: 检查位置并且吃掉食物，根据不同状态加载不同的图片
    if(!alive)
        return;
    this->eatFood();
    if(targetFood == nullptr)
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
        pix->load(IMAGE_BREEDER);
        switch(grow_stage)
        {
        case BREEDER_GROW_STAGE_SMALL:
        {
            pix_now = pix->copy(0, 0, FISH_WIDTH * 10, FISH_HEIGHT * 2);
            break;
        }
        case BREEDER_GROW_STAGE_MIDDLE:
        {
            pix_now = pix->copy(0, FISH_HEIGHT * 2, FISH_WIDTH * 10, FISH_HEIGHT * 2);
            break;
        }
        case BREEDER_GROW_STAGE_BIG:
        {
            pix_now = pix->copy(0, FISH_HEIGHT * 4, FISH_WIDTH * 10, FISH_HEIGHT * 2);
            break;
        }
        }
    }
    else
    {
        pix->load(IMAGE_HUNGRY_BREEDER);
        switch(grow_stage)
        {
        case BREEDER_GROW_STAGE_SMALL:
        {
            pix_now = pix->copy(0, 0, FISH_WIDTH * 10, FISH_HEIGHT * 2);
            break;
        }
        case BREEDER_GROW_STAGE_MIDDLE:
        {
            pix_now = pix->copy(0, FISH_HEIGHT * 2, FISH_WIDTH * 10, FISH_HEIGHT * 2);
            break;
        }
        case BREEDER_GROW_STAGE_BIG:
        {
            pix_now = pix->copy(0, FISH_HEIGHT * 4, FISH_WIDTH * 10, FISH_HEIGHT * 2);
            break;
        }
        }
    }

}

void Breeder::die()
{
    // TODO:加载死亡图片
    pix->load(IMAGE_DIE_BREEDER);
    switch(grow_stage)
    {
    case BREEDER_GROW_STAGE_SMALL:
    {
        pix_now = pix->copy(0,0, FISH_WIDTH * 10, FISH_HEIGHT * 2);
        break;
    }
    case BREEDER_GROW_STAGE_MIDDLE:
    {
        pix_now = pix->copy(0, FISH_HEIGHT * 2, FISH_WIDTH * 10, FISH_HEIGHT * 2);
        break;
    }
    case BREEDER_GROW_STAGE_BIG:
    {
        pix_now = pix->copy(0, FISH_HEIGHT * 4, FISH_WIDTH * 10, FISH_HEIGHT * 4);
        break;
    }
    }
    alive = false;
    QTimer::singleShot(1000, this, SLOT(sendDeadSignal()));
}

void Breeder::recieveFood(Food *food)
{
    // TODO:如果当前目标食物为空，则设置目标食物
    if(targetFood == nullptr && !food->isLocked() && full_value <= GET_FOOD_VALUE)
    {
        targetFood = food;
        food->beLocked();
        QObject::connect(food, SIGNAL(willBeDeleted()), this, SLOT(resetFood()));
    }
}

void Breeder::resetFood()
{
    // TODO:重置目标食物
    targetFood = nullptr;
}

void Breeder::createMoney()
{
    // TODO:发出创造金钱的信号
    c_count = 0;
    QPointF pos = scenePos();
    emit createFish(TYPE_GUPPI, pos.x(), pos.y());
}

int Breeder::type() const
{
    return TYPE_BREEDER;
}

void Breeder::growing()
{
    // TODO:增加成长时，并且根据成长时设置当前成长阶段
    age += 1;
    c_count += 1;
    if(age >= BREEDER_GROW_TO_BIG)
        grow_stage = BREEDER_GROW_STAGE_BIG;
    else if(age >= BREEDER_GROW_TO_MIDDLE)
        grow_stage = BREEDER_GROW_STAGE_MIDDLE;
    switch(grow_stage)
    {
    case BREEDER_GROW_STAGE_SMALL:
    {
        if(c_count >= BREEDER_CREATE_FISH_SMALL)
            createMoney();
        break;
    }
    case BREEDER_GROW_STAGE_MIDDLE:
    {
        if(c_count >= BREEDER_CREATE_FISH_MIDDLE)
            createMoney();
        break;
    }
    case BREEDER_GROW_STAGE_BIG:
    {
        if(c_count >= BREEDER_CREATE_FISH_BIG)
            createMoney();
        break;
    }
    }
}

Breeder::~Breeder()
{
    delete c_timer;
}
