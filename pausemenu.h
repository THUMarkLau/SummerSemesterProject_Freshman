#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <QWidget>
#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>
#include <QFont>
#include "gamecontroller.h"

/*
 * 暂停菜单
 */

class PauseMenu:public QWidget
{
    Q_OBJECT
public:
    PauseMenu(QWidget *parent = 0);
    ~PauseMenu();
    void setGameController(GameController *init); // 设置游戏控制器
    void setSceneCount(int count); // 设置场景
private:
    QPushButton *con_btn, *quit_btn;
    QLabel *title;
    GameController *controller;
    int temp_scene_count; // 用来在暂停时储存场景ID
signals:
    void continueButtonClicked();
    void quitButtonClicked();
public slots:
    void conBtnClicked();
    void quitBtnClicked();
};

#endif // PAUSEMENU_H
