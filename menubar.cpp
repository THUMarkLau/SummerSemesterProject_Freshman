#include "menubar.h"
#include "param.h"
#include <QSize>
#include <QtGlobal>
#include <QPainter>
#include <QTime>
#include <QDebug>

MenuBar::MenuBar(int stage,QWidget* parent):
    QWidget(parent), egg_level(0), money(200000),
    food_level(0),food_numlimit(1), buy(new QSound(SOUND_BUY)),
    shortofmoney(new QSound(SOUND_SHORTOFMONEY))
{
    // TODO:设置Menubar的参数，加载图片，设置背景图
    setFixedSize(1280, 130);
    setWindowFlag(Qt::FramelessWindowHint);
    egg.load(IMAGE_EGG);
    food.load(IMAGE_FOOD_ICON);
    food_n.load(IMAGE_LEVEL);

    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(IMAGE_BAR)));
    this->setPalette(palette);

    guppi_btn.setIcon(QIcon(IMAGE_GUPPI_ICON));
    guppi_btn.setIconSize(QSize(40, 40));
    guppi_btn.setGeometry(175, 30, 40, 40);
    guppi_btn.setParent(this);

    // TODO:根据不同场景加载和放置不同的部件
    if(stage == SCENE_GAME_ONE)
    {
        breeder_btn.setIcon(QIcon(IMAGE_BREEDER_ICON));
        breeder_btn.setIconSize(QSize(40, 40));
        breeder_btn.setGeometry(325,30,40,40);
        breeder_btn.setParent(this);
        breeder_money.setNum(PRICE_BREEDER);
        breeder_money.setParent(this);
        breeder_money.setGeometry(325, 91, 50, 30);
    }
    if(stage != SCENE_GAME_ONE)
    {
        predator_btn.setIcon(QIcon(IMAGE_PREDATOR_ICON));
        predator_btn.setIconSize(QSize(40, 40));
        predator_btn.setGeometry(770, 30, 40, 40);
        predator_btn.setParent(this);
        predator_money.setNum(PRICE_PREDATOR);
        predator_money.setParent(this);
        predator_money.setGeometry(770, 91, 80, 30);
    }

    if(stage == SCENE_GAME_THREE)
    {
        bigpredator_btn.setIcon(QIcon(IMAGE_BIGPREDATOR_ICON));
        bigpredator_btn.setIconSize(QSize(40, 40));
        bigpredator_btn.setGeometry(625, 30, 40, 40);
        bigpredator_btn.setParent(this);
        bigpredator_money.setNum(PRICE_BIGPREDATOR);
        bigpredator_money.setParent(this);
        bigpredator_money.setGeometry(605, 91, 90, 30);
    }

    egg_btn.setIcon(QIcon(egg.copy(0,0, EGG_WIDTH, EGG_HEIGHT)));
    egg_btn.setIconSize(QSize(EGG_WIDTH, EGG_HEIGHT));
    egg_btn.setGeometry(905, 30, EGG_WIDTH, EGG_HEIGHT);
    egg_btn.setParent(this);

    food_nums_btn.setIcon(QIcon(food_n.copy(0,0,FOOD_NUM_SIZE, FOOD_NUM_SIZE)));
    food_nums_btn.setIconSize(QSize(40, 40));
    if(stage == SCENE_GAME_ONE)
        food_nums_btn.setGeometry(625, 30, 40, 40);
    else
        food_nums_btn.setGeometry(325, 30, 40, 40);
    food_nums_btn.setParent(this);

    food_level_btn.setIcon(QIcon(food.copy(0,0,FOOD_NUM_SIZE,FOOD_NUM_SIZE)));
    food_level_btn.setIconSize(QSize(40, 40));
    food_level_btn.setGeometry(475, 30, 40, 40);
    food_level_btn.setParent(this);

    QFont font;
    font.setBold(true);
    font.setPointSize(10);
    money_label.setFont(font);
    money_label.setParent(this);
    money_label.setGeometry(1120, 85, 100, 30);
    money_label.setNum(200);

    guppi_money.setNum(PRICE_GUPPI);
    breeder_money.setNum(PRICE_BREEDER);
    egg_money.setNum(PRICE_EGG);
    food_level_money.setNum(FOOD_LEVEL_COST);
    food_limit_money.setNum(FOOD_NUM_COST);

    guppi_money.setParent(this);
    guppi_money.setGeometry(175, 91, 50, 30);



    egg_money.setParent(this);
    egg_money.setGeometry(900, 91, 60, 30);
    food_level_money.setParent(this);
    food_level_money.setGeometry(475, 91, 80, 30);
    food_limit_money.setParent(this);
    if(stage == SCENE_GAME_ONE)
        food_limit_money.setGeometry(625, 91, 80, 30);
    else
        food_limit_money.setGeometry(325,91,80,30);

    connect(&guppi_btn, SIGNAL(clicked()), this, SLOT(guppi_btn_clicked()));
    connect(&breeder_btn, SIGNAL(clicked(bool)), this, SLOT(breeder_btn_clicked()));
    connect(&predator_btn, SIGNAL(clicked(bool)), this, SLOT(predator_btn_clicked()));
    connect(&bigpredator_btn, SIGNAL(clicked(bool)), this, SLOT(bigpredator_btn_clicked()));
    connect(&egg_btn, SIGNAL(clicked(bool)), this, SLOT(egg_btn_clicked()));
    connect(&food_nums_btn, SIGNAL(clicked(bool)), this, SLOT(food_num_btn_clicked()));
    connect(&food_level_btn, SIGNAL(clicked(bool)), this, SLOT(food_level_btn_clicked()));

    hide();
}

void MenuBar::guppi_btn_clicked()
{
    // TODO:发出创造guppi的信号，并且扣除金钱
    if(money < PRICE_GUPPI)
    {
        shortofmoney->play();
        return;
    }
    emit moneyCost(-PRICE_GUPPI);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int x = (qrand() % (WIDTH_OF_WINDOW / 2)), y = 0;
    while(y < 200 || y > (HEIGHT_OF_WINDOW / 2 - FISH_HEIGHT))
        y = (qrand() % (HEIGHT_OF_WINDOW / 2));
    while(x < 0 || x * 2 > WIDTH_OF_WINDOW - FISH_WIDTH)
        x = (qrand() % (WIDTH_OF_WINDOW / 2));
    emit createFish(TYPE_GUPPI, x, y);
}

void MenuBar::breeder_btn_clicked()
{
     // TODO:发出创造breeder的信号，并且扣除金钱
    if(money < PRICE_BREEDER)
    {
        shortofmoney->play();
        return;
    }
    buy->play();
    emit moneyCost(-PRICE_BREEDER);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int x = (qrand() % (WIDTH_OF_WINDOW / 2)), y = 0;
    while(y < 200 || y > (HEIGHT_OF_WINDOW / 2 - FISH_HEIGHT))
        y = (qrand() % (HEIGHT_OF_WINDOW / 2));
    while(x < 0 || x * 2 > WIDTH_OF_WINDOW - FISH_WIDTH)
        x = (qrand() % (WIDTH_OF_WINDOW / 2));
    emit createFish(TYPE_BREEDER, x, y);
}

void MenuBar::refreshMoney(int mon)
{
    // TODO:刷新金钱
    money = mon;
    money_label.setNum(money);
    money_label.show();
}

void MenuBar::predator_btn_clicked()
{
     // TODO:发出创造predator的信号，并且扣除金钱
    if(money < PRICE_PREDATOR)
    {
        shortofmoney->play();
        return;
    }
    buy->play();
    emit moneyCost(-PRICE_PREDATOR);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int x = (qrand() % (WIDTH_OF_WINDOW / 2)), y = 0;
    while(y < 200 || y > (HEIGHT_OF_WINDOW / 2 - FISH_HEIGHT))
        y = (qrand() % (HEIGHT_OF_WINDOW / 2));
    while(x < 0 || x * 2 > WIDTH_OF_WINDOW - FISH_WIDTH)
        x = (qrand() % (WIDTH_OF_WINDOW / 2));
    emit createFish(TYPE_PREDATOR, x, y);
}

void MenuBar::bigpredator_btn_clicked()
{
     // TODO:发出创造big predator的信号，并且扣除金钱
    if(money < PRICE_BIGPREDATOR)
    {
        shortofmoney->play();
        return;
    }
    buy->play();
    emit moneyCost(-PRICE_BIGPREDATOR);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int x = (qrand() % (WIDTH_OF_WINDOW / 2)), y = 0;
    while(y < 200 || y > (HEIGHT_OF_WINDOW / 2 - BIGPREDATOR_SIZE))
        y = (qrand() % (HEIGHT_OF_WINDOW / 2));
    while(x < 0 || x * 2 > WIDTH_OF_WINDOW - BIGPREDATOR_SIZE)
        x = (qrand() % (WIDTH_OF_WINDOW / 2));
    emit createFish(TYPE_BIGPREDATOR, x, y);
}

void MenuBar::egg_btn_clicked()
{
    // TODO:购买宠物蛋，如果已经购买三次则发出胜利信号
    if(money < PRICE_EGG)
    {
        shortofmoney->play();
        return;
    }
    buy->play();
    money -= PRICE_EGG;
    emit moneyCost(-PRICE_EGG);
    ++egg_level;
    egg_btn.setIcon(QIcon(egg.copy(egg_level*EGG_WIDTH,0, EGG_WIDTH, EGG_HEIGHT)));
    egg_btn.show();
    if(egg_level == 2)
        emit gamePass();
}

void MenuBar::food_num_btn_clicked()
{
    // TODO:发出提高食物数量上限的信号并且扣除金钱
    if(food_numlimit == 8 || money < FOOD_NUM_COST)
    {
        shortofmoney->play();
        return;
    }
    buy->play();
    emit addFoodNum();
    ++food_numlimit;
    food_nums_btn.setIcon(QIcon(food_n.copy((food_numlimit-1)*FOOD_NUM_SIZE, 0,
                                            FOOD_NUM_SIZE, FOOD_NUM_SIZE)));
    food_nums_btn.show();
}

void MenuBar::food_level_btn_clicked()
{
    // TODO:发出提高食物等级的信号并且扣除金钱
    if(food_level == 2 || money < FOOD_LEVEL_COST)
    {
        shortofmoney->play();
        return;
    }
    buy->play();
    emit addFoodLevel();
    ++food_level;
    food_level_btn.setIcon(QIcon(food.copy(FOOD_NUM_SIZE*food_level, 0, FOOD_NUM_SIZE,FOOD_NUM_SIZE)));
    food_level_btn.show();
}
