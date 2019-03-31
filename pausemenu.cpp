#include "pausemenu.h"

PauseMenu::PauseMenu(QWidget *parent):
    QWidget(parent), con_btn(new QPushButton), quit_btn(new QPushButton),
    title(new QLabel)
{
    // TODO:设置button和label的参数和位置
    con_btn->setText("CONTINUE");
    quit_btn->setText("QUIT");
    con_btn->setFixedSize(300, 100);
    quit_btn->setFixedSize(300, 100);

    QFont font;
    font.setPointSize(30);
    font.setBold(true);
    title->setFont(font);
    title->setText("PAUSE MENU");

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(title, 0, Qt::AlignCenter);
    vLayout->addWidget(con_btn, 0, Qt::AlignCenter);
    vLayout->addWidget(quit_btn, 0, Qt::AlignCenter);

    setLayout(vLayout);

    connect(con_btn, SIGNAL(clicked(bool)), this, SLOT(conBtnClicked()));
    connect(quit_btn, SIGNAL(clicked(bool)), this, SLOT(quitBtnClicked()));
}

void PauseMenu::conBtnClicked()
{
    // TODO:发出continue按钮被按下的信号，并且改变场景
    emit continueButtonClicked();
    controller->setSceneCount(temp_scene_count);
    hide();
}

void PauseMenu::quitBtnClicked()
{
    // TODO:发出quit按钮被按下的信号，并且改变场景
    emit quitButtonClicked();
}

void PauseMenu::setGameController(GameController *init)
{
    // TODO:设置controller
    controller = init;
}

void PauseMenu::setSceneCount(int count)
{
    // TODO:设置场景
    temp_scene_count = count;
}

PauseMenu::~PauseMenu()
{
    delete con_btn;
    delete quit_btn;
    delete title;
}
