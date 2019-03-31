#include "gamecontroller.h"
#include "param.h"

GameController::GameController(MyScene *scene,QObject *parent):
    QObject(parent), scene(scene), timer(new QTimer),
    game_on(false),scene_count(SCENE_BEGIN_MENU), m_money(200000),
    food_level(0), max_food_num(1), foods(0), g_mummy(nullptr), snail(nullptr),
    timer_alien(new QTimer),fish_count(0),begin(false), alien_count(0),
    warnning(new QSound(SOUND_WARNNING)), drop(new QSound(SOUND_DROP)),
    die_sound(new QSound(SOUND_DIE))
{
    // TODO:初始化计时器，并且创造两条鱼
    timer->start(REFRESH_TIME);
    timer_alien->start(ALIEN_REFRESH_TIME);
    createFish(TYPE_GUPPI, 200, 300);
    pause();
}

void GameController::resume()
{
    // TODO: 链接计时器和需要更新的函数
    connect(timer, SIGNAL(timeout()), scene, SLOT(update()));
    connect(timer_alien, SIGNAL(timeout()), this, SLOT(alienComing()));

    // TODO:在新场景中添加宠物
    if((scene_count == SCENE_GAME_TWO || scene_count == SCENE_GAME_THREE)&& snail == nullptr)
    {
        snail = new Snail;
        scene->addItem(snail);
        connect(this, SIGNAL(gameStop()), snail, SLOT(gameStop()));
        connect(this, SIGNAL(gameContinue()), snail, SLOT(gameContinue()));
    }
    if(scene_count == SCENE_GAME_THREE && g_mummy == nullptr)
    {
        g_mummy = new GuppiMummy;
        scene->addItem(g_mummy);
        connect(this, SIGNAL(gameStop()), g_mummy, SLOT(gameStop()));
        connect(this, SIGNAL(gameContinue()), g_mummy, SLOT(gameContinue()));
    }
    if(g_mummy != nullptr)
        connect(g_mummy, SIGNAL(createGuppi(int,int,int)), this, SLOT(createFish(int,int,int)));
    connect(timer, SIGNAL(timeout()), this, SLOT(checkDeadAlien()));
    emit gameContinue();
    game_on = true;
}

void GameController::pause()
{
    // TODO:断开计时器和函数的链接并且发出游戏暂停的信号
    disconnect(timer, SIGNAL(timeout()), scene, SLOT(update()));
    disconnect(timer_alien, SIGNAL(timeout()), this, SLOT(alienComing()));
    emit gameStop();
    game_on = false;
}

bool GameController::isOn() const
{
    // TODO:返回记录游戏是否在进行中的变量
    return game_on;
}

int GameController::sceneCount() const
{
    // TODO:返回记录游戏场景的变量
    return scene_count;
}

void GameController::setSceneCount(int scenecount)
{
    // TODO:设置游戏场景，并根据场景来添加鱼
    scene_count = scenecount;
    if((scenecount == SCENE_GAME_TWO || scenecount == SCENE_GAME_THREE) && scene != nullptr && begin)
    {
        createFish(TYPE_GUPPI, 100, 100);
        gameStop();
        begin = false;
    }
}

void GameController::createFish(int type, int x, int y)
{
    // TODO: 根据鱼的种类和给的坐标在指定的位置产生一条鱼
    ++fish_count;
    switch (type) {
    case TYPE_GUPPI:
    {
        Guppi *guppi = new Guppi(x, y);
        scene->addItem(guppi);
        connect(this, SIGNAL(gameStop()), guppi, SLOT(gameStop()));
        connect(this, SIGNAL(gameContinue()), guppi, SLOT(gameContinue()));
        connect(this, SIGNAL(foodPos(Food*)), guppi, SLOT(recieveFoodPos(Food*)));
        connect(guppi, SIGNAL(moneyCreate(int,int,int)), this, SLOT(createMoney(int, int, int)));
        connect(guppi, SIGNAL(hasDead(Fish*)), this, SLOT(fishReduce(Fish*)));
        connect(guppi, SIGNAL(posInfo(Guppi*)), this, SLOT(postGuppiInfo(Guppi*)));
        connect(guppi, SIGNAL(hasDead(Fish*)), scene, SLOT(removeSlotItem(Fish*)));
        break;
    }
    case TYPE_BREEDER:
    {
        Breeder *breeder = new Breeder(x, y);
        scene->addItem(breeder);
        connect(this, SIGNAL(gameStop()), breeder, SLOT(gameStop()));
        connect(this, SIGNAL(gameContinue()), breeder, SLOT(gameContinue()));
        connect(this, SIGNAL(foodPos(Food*)), breeder, SLOT(recieveFood(Food*)));
        connect(breeder, SIGNAL(createFish(int,int,int)), this, SLOT(createFish(int,int,int)));
        connect(breeder, SIGNAL(hasDead(Fish*)), this, SLOT(fishReduce(Fish*)));
        connect(breeder, SIGNAL(hasDead(Fish*)), scene, SLOT(removeSlotItem(Fish*)));
        break;
    }
    case TYPE_PREDATOR:
    {
        Predator *predator = new Predator(x, y);
        scene->addItem(predator);
        connect(this, SIGNAL(gameStop()), predator, SLOT(gameStop()));
        connect(this, SIGNAL(gameContinue()), predator, SLOT(gameContinue()));
        connect(predator, SIGNAL(moneyCreate(int,int,int)), this, SLOT(createMoney(int,int,int)));
        connect(this, SIGNAL(guppiPos(Guppi*)), predator, SLOT(receiveFood(Guppi*)));
        connect(predator, SIGNAL(hasDead(Fish*)), this, SLOT(fishReduce(Fish*)));
        connect(predator, SIGNAL(selfInfo(Predator*)), this, SLOT(postPredatorInfo(Predator*)));
        connect(predator, SIGNAL(hasDead(Fish*)), scene, SLOT(removeSlotItem(Fish*)));
        break;
    }
    case TYPE_BIGPREDATOR:
    {
        BigPredator *bigpredator = new BigPredator(x, y);
        scene->addItem(bigpredator);
        connect(this, SIGNAL(gameStop()), bigpredator, SLOT(gameStop()));
        connect(this, SIGNAL(gameContinue()), bigpredator, SLOT(gameContinue()));
        connect(bigpredator, SIGNAL(moneyCreate(int,int,int)), this, SLOT(createMoney(int,int,int)));
        connect(bigpredator, SIGNAL(hasDead(Fish*)), scene, SLOT(removeSlotItem(Fish*)));
        connect(this, SIGNAL(predatorPos(Predator*)), bigpredator, SLOT(recieveFood(Predator*)));
        connect(bigpredator, SIGNAL(hasDead(Fish*)), this, SLOT(fishReduce(Fish*)));
    }
    default:
        break;
    }
}

void GameController::showBar()
{
    // TODO:展示menubar
    menubar->refreshMoney(m_money);
    menubar->show();
}

void GameController::setMenuBar(MenuBar *init)
{
    // TODO:设置menubar，并且链接相对应的函数
    menubar = init;
    if(init != nullptr)
    {
        connect(menubar, SIGNAL(createFish(int,int,int)), this, SLOT(createFish(int,int,int)));
        connect(menubar, SIGNAL(moneyCost(int)), this, SLOT(moneyChanged(int)));
        connect(menubar, SIGNAL(gamePass()), this, SLOT(getGameInfo()));
        connect(menubar, SIGNAL(addFoodNum()), this, SLOT(addFoodLimit()));
        connect(menubar, SIGNAL(addFoodLevel()),this, SLOT(addFoodLevel()));
    }
}

void GameController::createFood(int x, int y)
{
    // TODO:根据给出的坐标在指定的位置创造食物，
    //      如果食物已经到达上限或者金钱不足就返回
    if(foods >= max_food_num || m_money < 5)
        return;
    Food *food = new Food(food_level, x, y);
    if(food != nullptr)
    {
        connect(this, SIGNAL(gameStop()), food, SLOT(gameStop()));
        connect(this, SIGNAL(gameContinue()), food, SLOT(gameContinue()));
        connect(food, SIGNAL(toBeDeleted(Food*)), this, SLOT(deducteFood(Food*)));
        connect(food, SIGNAL(position(Food*)), this, SLOT(getFoodPos(Food*)));
        scene->addItem(food);
        ++foods;
    }
    drop->play();
    m_money -= 5;
    menubar->refreshMoney(m_money);
}

void GameController::deducteFood(Food* food)
{
    // TODO:删除食物，并且减少食物总数
    delete food;
    --foods;
}

void GameController::getFoodPos(Food* food)
{
    // TODO:发送食物的指针
    emit foodPos(food);
}

void GameController::createMoney(int level, int x, int y)
{
    // TODO:根据给出的等级和坐标在指定位置创造制定等级的金钱
    Money *money = new Money(level, x, y);
    connect(this, SIGNAL(gameStop()), money, SLOT(gameStop()));
    connect(this, SIGNAL(gameContinue()), money, SLOT(gameContinue()));
    connect(money, SIGNAL(getClicked(int,Money*)), this, SLOT(addMoney(int,Money*)));
    if(snail != nullptr)
    {
        connect(money, SIGNAL(deleteSelf(Money*)), this, SLOT(removeMoney(Money*)));
        connect(money, SIGNAL(posInfo(Money*)), snail, SLOT(recievePos(Money*)));
    }
    scene->addItem(money);
}

void GameController::addMoney(int value, Money *money)
{
    // TODO:将消失的金钱的值加入钱的总数中并且刷新金钱
    m_money += value;
    menubar->refreshMoney(m_money);
}

void GameController::removeMoney(Money *money)
{
    // TODO:删除money
    if(snail != nullptr)
        snail->moneyDelete(money);
    delete money;
}

void GameController::createAlien()
{
    // TODO:在随机的位置创造随机种类的外星人
    if(!game_on)
        return;
    if(scene_count != SCENE_GAME_ONE && scene_count != SCENE_GAME_TWO && scene_count != SCENE_GAME_THREE)
        return;
    if(alien_count >= 1)
        return;
    if(snail != nullptr)
    {
        snail->alienComing(true);
    }
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int randnum = qrand();
    switch(randnum % 3)
    {
    case RED_ALIEN_ID:
    case BLUE_ALIEN_ID:
    {
        Alien* alien = new Alien(randnum%2);
        scene->addItem(alien);
        connect(this, SIGNAL(gameStop()), alien, SLOT(gameStop()));
        connect(this, SIGNAL(gameContinue()), alien, SLOT(gameContinue()));
        break;
    }
    case GUS_ALIEN_ID:
    {
        Alien *alien = new Alien(GUS_ALIEN_ID);
        scene->addItem(alien);
        connect(this, SIGNAL(gameStop()), alien, SLOT(gameStop()));
        connect(this, SIGNAL(gameContinue()), alien, SLOT(gameContinue()));
        break;
    }
    }
    alien_count++;
}

void GameController::postGuppiInfo(Guppi *guppi)
{
    // TODO:发送Guppi的位置
    emit guppiPos(guppi);
}

void GameController::postPredatorInfo(Predator *predator)
{
    // TODO:发送食肉鱼的指针
    emit predatorPos(predator);
}

void GameController::moneyChanged(int gap)
{
    // TODO:将改变增加到总钱数中，并更新金钱
    m_money += gap;
    menubar->refreshMoney(m_money);
}

void GameController::getGameInfo()
{
    // TODO: 重置，并发出过关信息
    reset();
    emit gamePass(scene_count);
}

void GameController::setScene(MyScene *sc)
{
    // TODO:设置场景
    scene = sc;
}

void GameController::reset()
{
    // TODO:将所有变量改为初始值
    game_on = false;
    menubar = nullptr;
    food_level = 0;
    max_food_num = 1;
    foods = 0;
    m_money = 200000;
    fish_count = 0;
    snail = nullptr;
    g_mummy = nullptr;
    begin = true;
    alien_count = 0;
}

void GameController::alienComing()
{
    // TODO:发出警报
    if(scene_count != SCENE_GAME_ONE && scene_count != SCENE_GAME_TWO && scene_count != SCENE_GAME_THREE)
        return;
    QTimer::singleShot(1000, this, SLOT(createAlien()));
    warnning->play(); 
}

void GameController::checkDeadAlien()
{
    // TODO:删除死亡的外星人和无用的金钱
    QList<QGraphicsItem*>list = scene->items();
    for(int index = 0; index < list.size(); ++index)
    {
        if(list[index]->type() == TYPE_ALIEN)
        {
            Alien* alien = qgraphicsitem_cast<Alien*>(list[index]);
            if(!alien->isAlive())
            {
                QPointF pos = alien->scenePos();
                createMoney(4, pos.x(), pos.y());
                scene->removeItem(alien);
                delete alien;
                if(snail != nullptr)
                {
                    snail->alienComing(false);
                }
                alien_count--;
            }
        }
        else if(list[index]->type() == TYPE_MONEY)
        {
            Money* money = qgraphicsitem_cast<Money*>(list[index]);
            if(!money->isAlive())
            {
                if(snail != nullptr)
                    snail->moneyDelete(money);
                scene->removeItem(money);
                delete money;
            }
        }
    }
}

void GameController::addFoodLimit()
{
    // TODO:增加食物的总数上限
    ++max_food_num;
    m_money -= FOOD_NUM_COST;
    menubar->refreshMoney(m_money);
}

void GameController::addFoodLevel()
{
    // TODO:提高食物的等级
    ++food_level;
    m_money -= FOOD_LEVEL_COST;
    menubar->refreshMoney(m_money);
}

void GameController::fishReduce(Fish* fish)
{
    // TODO:减少鱼的总数，并且判断是否失败
    Q_UNUSED(fish);
    --fish_count;
    die_sound->play();
    if(fish_count <= 0)
    {
        QTimer::singleShot(1000, this, SIGNAL(gameLost()));
        pause();
        setSceneCount(SCENE_DEFEAT);
    }
}
