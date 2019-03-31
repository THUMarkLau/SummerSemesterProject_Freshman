#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), scene(new MyScene(this)),
    menubar(new MenuBar(SCENE_GAME_ONE,this)), background_sound(new QSound(SOUND_BACKGROUND_MUSIC)),
    view(new QGraphicsView(this)), controller(new GameController(scene, this))
{
    // TODO：初始化部件
    loading.setParent(this);
    pause.setParent(this);
    pause.hide();
    pause.setGameController(controller);

    // TODO:初始化窗口参数
    QIcon icon = QIcon(IMAGE_ICON);
    setWindowIcon(icon);
    setWindowFlags(this->windowFlags() &~ Qt::WindowMinMaxButtonsHint);
    setWindowFlag(Qt::FramelessWindowHint);
    controller->setMenuBar(menubar);
    setFixedSize(1280, 720);
    setCentralWidget(&loading);
    loading.Loading();
    QTimer::singleShot(1000, this, SLOT(setMenuCentral()));

    // TODO:设置链接
    connect(&menu, SIGNAL(getStarted()), this, SLOT(loadingScene()));
    connect(&menu, SIGNAL(getStarted()), controller, SLOT(resume()));
    connect(&menu, SIGNAL(getQuited()), this, SLOT(close()));
    connect(&pause, SIGNAL(quitButtonClicked()), this, SLOT(close()));
    connect(&pause, SIGNAL(continueButtonClicked()), controller, SLOT(resume()));
    connect(controller, SIGNAL(gamePass(int)), this, SLOT(stageChanged(int)));
    connect(controller, SIGNAL(gameLost()), this, SLOT(gameLost()));

    // TODO:播放背景音乐
    background_sound->setLoops(QSound::Infinite);
    background_sound->play();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initScene()
{
    // TODO:初始化第一关的背景
    scene->setSceneRect(0, 0, WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW);
    view->setFixedSize(WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setScene(scene);
    controller->setSceneCount(SCENE_GAME_ONE);
}

void MainWindow::initSceneBackground()
{
    //TODO: 设置背景图片
    view->setBackgroundBrush(QPixmap(IMAGE_BACKGROUND));
    controller->showBar();
    //view->setCacheMode(QGraphicsView::CacheBackground);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // TODO:如果按下ESC键则跳出暂停窗口
    if(event->key() == Qt::Key_Escape)
    {
        if(controller->sceneCount() == SCENE_BEGIN_MENU)
        {
            this->close();
        }
        else if(controller->sceneCount() != SCENE_PAUSE)
        {
            controller->pause();
            pause.setSceneCount(controller->sceneCount());
            controller->setSceneCount(SCENE_PAUSE);
            pause.move(300,100);
            pause.show();
        }
    }
}

void MainWindow::loadingScene()
{
    // TODO:展示加载场景，并加载游戏
    controller->setSceneCount(SCENE_LOADING);
    initScene();
    initSceneBackground();
    setViewCentralWidget();
}

void MainWindow::setViewCentralWidget()
{
    // TODO: 将view设置为中心组件
    centralWidget()->setParent(0);
    setCentralWidget(view);
    controller->setSceneCount(SCENE_GAME_ONE);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // TODO:判断鼠标的位置，并产生食物
    switch (controller->sceneCount()) {
    case SCENE_BEGIN_MENU:
    case SCENE_HELP:
    case SCENE_PAUSE:
        break;
    case SCENE_GAME_ONE:
    case SCENE_GAME_TWO:
    case SCENE_GAME_THREE:
    {
        if(controller->isOn())
        {
            if(!menubar->geometry().contains(event->pos()))
            {
                controller->createFood(event->x() / 2, event->y() / 2);
            }
        }
    }
    }
}

void MainWindow::stageChanged(int stage)
{
    // TODO:删除上一个场景，加载下一个场景
    if(stage >= SCENE_GAME_ONE)
        deleteLastStage();
    initStage(stage + 1);
}

void MainWindow::deleteLastStage()
{
    // TODO:删除上一个场景的scene和view
    if(centralWidget() != nullptr)
        centralWidget()->setParent(0);
    delete scene;
    delete view;
}

void MainWindow::initStage(int stage)
{
    // TODO:重新建立scene和view，并设置其参数
    scene = new MyScene(this);
    view = new QGraphicsView(this);
    controller->setScene(scene);
    view->setScene(scene);
    scene->setSceneRect(0, 0, WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW);
    view->setFixedSize(WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    if(centralWidget() != nullptr)
        centralWidget()->setParent(0);
    setCentralWidget(view);

    // TODO:根据需要加载的场景执行不同的加载操作
    switch(stage)
    {
    case SCENE_HATCH_SCREEN:
    {
        delete menubar;
        controller->setMenuBar(nullptr);
        controller->setSceneCount(SCENE_HATCH_SCREEN);
        view->setBackgroundBrush(QPixmap(IMAGE_HATCH_SCREEN));
        continue_btn.setStyleSheet("background: argb(100, 0, 0, 0)");
        continue_btn.setGeometry(370, 670, 540, 50);
        continue_btn.setParent(this);
        continue_btn.show();
        connect(&continue_btn, SIGNAL(clicked(bool)), this, SLOT(hatchEnd()));
        menubar = nullptr;
        break;
    }
    case SCENE_GAME_TWO:
    {
        if(menubar != nullptr)
            delete menubar;
        menubar = new MenuBar(SCENE_GAME_TWO, this);
        controller->setMenuBar(menubar);
        controller->setSceneCount(SCENE_GAME_TWO);
        view->setBackgroundBrush(QPixmap(IMAGE_BACKGROUND));
        controller->showBar();
        break;
    }
    case SCENE_SECOND_HATCH_SCREEN:
    {
        delete menubar;
        controller->setMenuBar(nullptr);
        controller->setSceneCount(SCENE_SECOND_HATCH_SCREEN);
        view->setBackgroundBrush(QPixmap(IMAGE_SECOND_HATCH_SCREEN));
        se_continue_btn.setStyleSheet("background: argb(100, 0, 0, 100)");
        se_continue_btn.setGeometry(370, 670, 540, 50);
        se_continue_btn.setParent(this);
        se_continue_btn.show();
        connect(&se_continue_btn, SIGNAL(clicked(bool)), this, SLOT(hatchEnd()));
        menubar = nullptr;
        break;
    }
    case SCENE_GAME_THREE:
    {
        if(menubar != nullptr)
            delete menubar;
        menubar = new MenuBar(SCENE_GAME_THREE, this);
        controller->setMenuBar(menubar);
        controller->setSceneCount(SCENE_GAME_THREE);
        view->setBackgroundBrush(QPixmap(IMAGE_BACKGROUND));
        controller->showBar();
        break;
    }
    case SCENE_DEFEAT:
    {
        view->setBackgroundBrush(QPixmap(IMAGE_DEFEAT));
        controller->setSceneCount(SCENE_DEFEAT);
        break;
    }
    case SCENE_VICTORY:
    {
        view->setBackgroundBrush(QPixmap(IMAGE_VICTORY));
        controller->setSceneCount(SCENE_VICTORY);
        v_quitbtn.setStyleSheet("background: argb(100, 0, 0, 0)");
        v_quitbtn.setGeometry(472, 526, 343, 138);
        connect(&v_quitbtn, SIGNAL(clicked(bool)), this, SLOT(close()));
        v_quitbtn.setParent(this);
        v_quitbtn.show();
        break;
    }
    }
    pause.setParent(0);
    pause.setParent(this);
    controller->resume();
}

void MainWindow::setMenuCentral()
{
    // TODO:将开始菜单设置为中心部件
   centralWidget()->setParent(0);
   setCentralWidget(&menu);
   loading.close();
}

void MainWindow::hatchEnd()
{
    // TODO:结束hatch场景，并加载下一场景
    switch(controller->sceneCount())
    {
    case SCENE_HATCH_SCREEN:
    {
        continue_btn.hide();
        stageChanged(SCENE_HATCH_SCREEN);
        break;
    }
    case SCENE_SECOND_HATCH_SCREEN:
    {
        se_continue_btn.hide();
        stageChanged(SCENE_SECOND_HATCH_SCREEN);
        break;
    }
    }
}

void MainWindow::gameLost()
{
    // TODO：删除场景，并且加载失败场景
    deleteLastStage();
    initStage(SCENE_DEFEAT);
    quit_btn.setStyleSheet("background: argb(100, 0, 0, 0)");
    quit_btn.setGeometry(457, 605, 368, 82);
    quit_btn.setParent(this);
    quit_btn.show();
    connect(&quit_btn, SIGNAL(clicked(bool)), this, SLOT(close()));
}
