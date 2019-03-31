#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>
#include <QFont>
#include <QSpacerItem>
#include <QPalette>
#include <QBrush>
#include <QPainter>
#include <QColor>
#include "param.h"

/*
 * 开始界面菜单
 */

class Menu:public QWidget
{
    Q_OBJECT
public:
    Menu(QWidget *parent = 0);
    ~Menu();
signals:
    void getStarted(); // 开始信号
    void getQuited(); // 退出信号
//protected:
//    void paintEvent(QPaintEvent *event);
private slots:
    void startButtonClicked(); // 开始键被按下
    void quitButtonClicked(); // 退出键被按下
private:
    QPushButton *startButton, *quitButton;
    QLabel *title;
};

#endif // MENU_H
