#include "alien.h"
#include "param.h"

Alien::Alien(int alien_type, QObject *parent):
    QObject(parent), pix_all(new QPixmap), right(true),
    timer(new QTimer), pix_index(0), alive(true), m_type(alien_type),
    punch(new QSound(SOUND_PUNCH))
{
    // TODO:根据不同的外星人类型加载其图片并设置其生命值
    switch(alien_type)
    {
    case BLUE_ALIEN_ID:
    {
        pix_all->load(IMAGE_BLUE_ALIEN);
        lifetime = BLUE_ALIEN_LIFE;
        break;
    }
    case RED_ALIEN_ID:
    {
        pix_all->load(IMAGE_RED_ALIEN);
        lifetime = RED_ALIEN_LIFE;
        break;
    }
    case GUS_ALIEN_ID:
    {
        pix_all->load(IMAGE_GUS);
        lifetime = GUS_ALIEN_LIFE;
        break;
    }
    }
    pix_turn = pix_all->copy(0, 0, ALIEN_SIZE * 10, ALIEN_SIZE);
    timer->start(REFRESH_TIME);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveForward()));

    // TODO:产生一个合法的随即坐标
    int x = -1, y = -1;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    while(x <= 0 || x*2 >= (WIDTH_OF_WINDOW - ALIEN_SIZE))
    {
        x = qrand() % ((WIDTH_OF_WINDOW - ALIEN_SIZE) * 2);
    }
    while(y*2 <= HEIGHT_OF_BAR || y*2 >= HEIGHT_OF_WINDOW - ALIEN_SIZE)
    {
        y = qrand() % ((HEIGHT_OF_WINDOW - ALIEN_SIZE) * 2);
    }
    setPos(x, y);
}

QRectF Alien::boundingRect() const
{
    QPointF pos = scenePos();
    return QRectF(pos.x(), pos.y(), ALIEN_SIZE, ALIEN_SIZE);
}

void Alien::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    // TODO:根据方向和帧数产生当前帧的图片
    pix_index %= 10;
    if(right)
    {
        pix_turn = pix_all->copy(0, 0, ALIEN_SIZE * 10, ALIEN_SIZE);
    }
    else
    {
        pix_turn = pix_all->copy(0, ALIEN_SIZE, ALIEN_SIZE * 10, ALIEN_SIZE);
    }
    pix_now = pix_turn.copy(ALIEN_SIZE * pix_index, 0, ALIEN_SIZE, ALIEN_SIZE);
    QPointF pos = scenePos();
    painter->drawPixmap(pos.x(), pos.y(), ALIEN_SIZE, ALIEN_SIZE, pix_now);
    ++pix_index;
}

void Alien::gameStop()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(moveForward()));
}

void Alien::gameContinue()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(moveForward()));
}

void Alien::moveForward()
{
    // TODO:检查是否存活
    if(!alive)
    {
        return;
    }
    QPointF pos = scenePos();
    // TODO:检查位置并清理碰撞的鱼
    checkPos();
    killFish();
    if(!alive)
    {
        return;
    }
    // TODO:根据参数判断移动方向
    if(right)
        pos.setX(pos.x() + 3);
    else
        pos.setX(pos.x() - 3);
    if(down)
        pos.setY(pos.y() + 2);
    else
        pos.setY(pos.y() - 2);
    if(!alive)
        return;
    setPos(pos);
    prepareGeometryChange();
}

void Alien::checkPos()
{
    // TODO:检查位置
    QPointF pos = scenePos();
    if(pos.x() * 2 >= WIDTH_OF_WINDOW - ALIEN_SIZE)
    {
        right = false;
    }
    if(pos.x() <= 0)
    {
        right = true;
    }
    if(pos.y() * 2 >= HEIGHT_OF_WINDOW - ALIEN_SIZE)
    {
        down = false;
    }
    if(pos.y() * 2 <= HEIGHT_OF_BAR + 30)
    {
        down = true;
    }
}

void Alien::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // TODO:被鼠标点击时发生减少生命值
    if(m_type == GUS_ALIEN_ID)
        return;
    punch->play();
    lifetime -= 10;
    QPointF pos = scenePos();
    if(event->pos().x() < pos.x() + ALIEN_SIZE/2 )
        right = true;
    else
        right = false;
    if(event->pos().y() < pos.y() + ALIEN_SIZE/2)
        down = true;
    else
        down = false;
    checkLife();
}

void Alien::checkLife()
{
    if(lifetime > 0)
        return;
    // 死亡的情况
    alive = false;
}

void Alien::killFish()
{
    // TODO:从被碰撞的物体中找出鱼并判其死亡
    QList<QGraphicsItem*> items = collidingItems();
    if(m_type == GUS_ALIEN_ID)
    {
        for(int index = 0; index < items.size(); ++index)
        {
            if(items[index]->type() == TYPE_GUPPI || items[index]->type() == TYPE_BIGPREDATOR ||
                    items[index]->type() == TYPE_BREEDER || items[index]->type() == TYPE_PREDATOR)
            {
                Fish* fish = qgraphicsitem_cast<Fish*>(items[index]);
                fish->sendDeadSignal();
                lifetime -= 30;
            }
            else if(items[index]->type() == TYPE_FOOD)
            {
                Food* food = qgraphicsitem_cast<Food*>(items[index]);
                food->beEaten();
                lifetime -= 20;
            }
        }
        checkLife();
    }
    else
    {
        for(int index = 0; index < items.size(); ++index)
        {
            if(items[index]->type() == TYPE_GUPPI || items[index]->type() == TYPE_BIGPREDATOR ||
                    items[index]->type() == TYPE_BREEDER || items[index]->type() == TYPE_PREDATOR)
            {
                Fish* fish  = qgraphicsitem_cast<Fish*>(items[index]);
                fish->sendDeadSignal();
            }
        }
    }
}

int Alien::type() const
{
    // TODO:返回其类型
    return TYPE_ALIEN;
}

Alien::~Alien()
{
    delete timer;
    delete pix_all;
}

bool Alien::isAlive() const
{
    return alive;
}
