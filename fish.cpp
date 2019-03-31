#include "fish.h"
#include "param.h"
#include <QDebug>
#include <QPointF>

Fish::Fish(QObject *parent):
    QObject(parent), age(0), hungry(false),
    timer(new QTimer), grow_stage(0),pix(new QPixmap), targetFood(nullptr),
    count_down(0), count_right(0), alive(true), full_value(100), money_time(0),
    hori_lock(false), vert_lock(false), eat(new QSound(SOUND_EAT)), move_index(10)
{
    // TODO:初始化计时器
    timer->start(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(becomeHungry()));
    connect(timer, SIGNAL(timeout()), this, SLOT(growing()));
    connect(timer, SIGNAL(timeout()), this, SLOT(moveForward()));
}

void Fish::becomeHungry()
{
    // TODO:减少饱腹值，并且根据其值来判断状态
    --full_value;
    if(full_value <= HUNGRY_VALUE && !hungry)
    {
        hungry = true;
    }
    if(full_value > HUNGRY_VALUE && hungry)
        hungry = false;
    if(full_value < DIE_VALUE)
    {
        die();
    }
}

void Fish::feed(int feed_value)
{
    // TODO:吃到食物，改变饱腹值
    hungry = false;
    full_value = feed_value;
}

void Fish::moveForward()
{
    // TODO:根据参数设定前进方向
    QPointF pos = scenePos();
    checkPos(pos);
    ++move_index;
    if(!alive)
    {
        pos.setY(pos.y() + 5);
        return;
    }
    if(!hori_lock)
        if(count_right % 2 == 0)
        {
            if(!hungry || targetFood == nullptr)
            {
                if(move_index < FISH_MOVE_TIME)
                    return;
                pos.setX(pos.x() + 4);
                if(move_index > FISH_MOVE_TIME + FISH_LAST_TIME)
                    move_index = 0;
            }
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
            if(!hungry || targetFood == nullptr)
            {

                pos.setY(pos.y() + 4);
            }
            else
            {
                if(abs(full_value) <= 50)
                    pos.setY(pos.y() + 4 + static_cast<int>(abs(full_value) * 0.05));
                else
                    pos.setY(pos.y() + 6);
            }
        }
        else
            pos.setY(pos.y() - 4);
    setPos(pos);
}

void Fish::sendDeadSignal()
{
    // TODO:发出死亡信号
    emit hasDead(this);
}

void Fish::gameStop()
{
    // TODO:断开所有计时器的链接
    disconnect(timer, SIGNAL(timeout()), this, SLOT(becomeHungry()));
    disconnect(timer, SIGNAL(timeout()), this, SLOT(growing()));
    disconnect(timer, SIGNAL(timeout()), this, SLOT(moveForward()));
}

void Fish::gameContinue()
{
    //TODO:将所有计时器链接
    connect(timer, SIGNAL(timeout()), this, SLOT(becomeHungry()));
    connect(timer, SIGNAL(timeout()), this, SLOT(growing()));
    connect(timer, SIGNAL(timeout()), this, SLOT(moveForward()));
}

void Fish::eatFood()
{
    // TODO:判断与目标食物的距离，如果近则吃掉目标食物
    if(targetFood == nullptr)
        return;
    QPointF my_pos = scenePos(), food_pos = targetFood->scenePos();
    int gap_x = my_pos.x() - food_pos.x();
    int gap_y = my_pos.y() - food_pos.y();
    if(gap_x < 0 && gap_x > GAP_X_LOCK_RIGHT_FOOD)
        hori_lock = true;
    else if(gap_x > 0 && gap_x < GAP_X_LOCK_LEFT_FOOD)
        hori_lock = true;
    else
        hori_lock = false;
    if(abs(gap_y) < GAP_Y_LOCK_FOOD)
        vert_lock = true;
    else
        vert_lock = false;
    if(hori_lock && vert_lock)
    {
        eat->play();
        feed(targetFood->Level() * 60 + 100);
        targetFood->beEaten();
        targetFood = nullptr;
        hori_lock = false;
        vert_lock = false;
    }
}

Fish::~Fish()
{
    delete pix;
    delete timer;
}
