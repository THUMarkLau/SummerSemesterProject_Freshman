#ifndef MENUBAR_H
#define MENUBAR_H

#include <QWidget>
#include <QPixmap>
#include <QPalette>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QtMultimedia/QSound>

/*
 * 游戏中的菜单栏
 */

class MenuBar:public QWidget
{
    Q_OBJECT
public:
    MenuBar(int stage, QWidget *parent = 0);
    void refreshMoney(int mon);
private:
    /*
     * 菜单栏中的每个物品都使用QPushButton来承载
     */
    QPushButton guppi_btn;
    QPushButton breeder_btn;
    QPushButton predator_btn;
    QPushButton bigpredator_btn;
    QPushButton egg_btn;
    QPushButton food_nums_btn, food_level_btn;
    QLabel money_label;
    QLabel guppi_money, breeder_money, predator_money, bigpredator_money, egg_money;
    QLabel food_level_money, food_limit_money;
    QSound *buy, *shortofmoney;
    int money;
    int egg_level; // 蛋的等级
    int food_level; // 食物的等级
    int food_numlimit; // 食物的数量上限
    QPixmap egg; // 蛋的图片
    QPixmap food; // 食物的图片
    QPixmap food_n; // 食物数量的图片
private slots:
    void guppi_btn_clicked();
    void breeder_btn_clicked();
    void predator_btn_clicked();
    void bigpredator_btn_clicked();
    void egg_btn_clicked();
    void food_num_btn_clicked();
    void food_level_btn_clicked();
signals:
    void createFish(int type, int x , int y);
    void moneyCost(int cost);
    void gamePass(); // 游戏通过
    void addFoodNum();
    void addFoodLevel();
};

#endif // MENUBAR_H
