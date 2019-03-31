#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QPixmap>
#include <QKeyEvent>
#include <QPalette>
#include <QColor>
#include <QTimer>
#include <QRect>
#include <QtMultimedia/QSound>
#include "gamecontroller.h"
#include "menu.h"
#include "param.h"
#include "pausemenu.h"
#include "loadingwidget.h"
#include "myscene.h"
#include "menubar.h"
#include "food.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MyScene * scene; // 场景
    QGraphicsView *view; // 视角
    GameController *controller; // 游戏控制器
    Menu menu; // 开始菜单
    PauseMenu pause; // 暂停菜单
    LoadingWidget loading; // 加载画面
    MenuBar *menubar; // 游戏上方的选择条
    QPushButton continue_btn, se_continue_btn; // 按键
    QPushButton quit_btn; // 游戏失败的退出按钮
    QPushButton v_quitbtn; // 游戏成功的退出按钮
    QSound *background_sound; // 背景音乐
    void keyPressEvent(QKeyEvent *event); // 重载键盘事件
    void mousePressEvent(QMouseEvent *event); // 重载鼠标事件
public slots:
    void stageChanged(int stage); // 场景发生变化
    void gameLost(); // 游戏失败
private slots:
    void initScene(); // 初始化场景
    void initSceneBackground(); // 初始化背景
    void loadingScene(); // 加载场景
    void setViewCentralWidget(); // 把view设置为中心元件
    void setMenuCentral(); // 把菜单设置为中心物件
    void hatchEnd(); // hatch界面结束
private:
    void deleteLastStage(); // 删除上一个场景
    void initStage(int stage); // 构建场景
};

#endif // MAINWINDOW_H
