#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H


#include <QTimer>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QObject>
#include <QtMultimedia/QSound>
#include <QTime>
#include "menubar.h"
#include "guppi.h"
#include "myscene.h"
#include "food.h"
#include "money.h"
#include "alien.h"
#include "guppimummy.h"
#include "snail.h"
#include "breeder.h"
#include "predator.h"
#include "bigpredator.h"

/*
 * GameController类用于控制游戏
 */

class GameController: public QObject
{
    Q_OBJECT
public:
    GameController(MyScene *scene,QObject *parent = 0);
    MyScene *scene;
    void setMenuBar(MenuBar*); // 设置menubar
    bool isOn() const; // 返回游戏是否开始
    int sceneCount() const; // 返回游戏场景
    void setSceneCount(int scenecount); // 设置场景
    void showBar(); // 展示menubar
    void setScene(MyScene*); // 设置scene
signals:
    void gameStop(); // 游戏暂停的信号
    void gameContinue(); // 游戏继续的信号
    void foodPos(Food*); // 发送食物的信息
    void guppiPos(Guppi*); // 发送Guppi的信息
    void predatorPos(Predator*); // 发送Predator的指针
    void gamePass(int); // 发送游戏通过的信息
    void gameLost(); // 游戏失败
public slots:
    void createFish(int type, int x, int y); // 创造鱼的函数
    void pause(); // 暂停函数
    void resume(); // 继续函数
    void createFood(int x, int y); //level表示食物的等级，xy为坐标
    void deducteFood(Food* food); // 食物减少
    void getFoodPos(Food*); // 得到食物的位置
    void createMoney(int level, int x, int y);// 创建金钱
    void addMoney(int value, Money*);// 增加金钱
    void removeMoney(Money*); // 移除金钱
    void createAlien(); // 产生外星人
    void postGuppiInfo(Guppi*); // 散布Guppi的信息
    void postPredatorInfo(Predator*); // 散布Predator的信息
    void moneyChanged(int gap); // 钱发生变化
    void getGameInfo(); // 接受游戏通过的信息
    void addFoodLimit(); // 增加食物的最大数量
    void addFoodLevel(); // 升级食物
    void fishReduce(Fish*); // 鱼减少了
private:
    QTimer *timer;
    QTimer *timer_alien; // 记录外星人出现
    GuppiMummy *g_mummy; // 古比妈咪
    Snail *snail; // 蜗牛
    bool game_on; // 用来判断游戏是否开始
    bool begin; // 判断当前是否是每一关刚开始的状态
    int scene_count; // 判断游戏的场景
    MenuBar *menubar; // 菜单栏
    int food_level; // 食物的等级
    int max_food_num; // 食物存在的最大数量
    int foods; // 食物的总数
    int m_money; // 金钱
    int fish_count; // 记录鱼的总数
    void reset(); // 重置函数
    QSound *warnning, *drop, *die_sound; // 音效
    int alien_count;
private slots:
    void alienComing(); // 外星人即将出现
    void checkDeadAlien(); // 检查外星人是否死亡
};

#endif // GAMECONTROLLER_H
