#include "menu.h"
#include <QDebug>

Menu::Menu(QWidget *parent):
    QWidget(parent), startButton(new QPushButton), quitButton(new QPushButton),
     title(new QLabel)
{
    // TODO:初始化按钮，并将其设置在正确的位置
    startButton->setText("START");
    quitButton->setText("QUIT");
    //helpButton->setText("HELP");
    title->setText("MENU");

    QFont *font = new QFont;
    font->setPointSize(30);
    font->setBold(true);
    title->setFont(*font);
    QSpacerItem* spacer = new QSpacerItem(70,250);

    startButton->setFixedSize(300, 100);
    quitButton->setFixedSize(300, 100);
    //helpButton->setFixedSize(300, 100);

    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(IMAGE_MENU)));             // 使用平滑的缩放方式
    this->setPalette(palette);                           // 给widget加上背景图

    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->addWidget(title, 0, Qt::AlignCenter);
    vLayout->addSpacerItem(spacer);
    vLayout->addWidget(startButton, 0, Qt::AlignCenter);
   // vLayout->addWidget(helpButton, 0, Qt::AlignCenter);
    vLayout->addWidget(quitButton, 0, Qt::AlignCenter);
    setLayout(vLayout);


    connect(startButton, SIGNAL(clicked(bool)), this, SLOT(startButtonClicked()));
    connect(quitButton, SIGNAL(clicked(bool)), this, SLOT(quitButtonClicked()));
}

void Menu::startButtonClicked()
{
    // TODO:关闭Menu，并且发出开始信号
    close();
    emit getStarted();
}

void Menu::quitButtonClicked()
{
    // TODO:发出关闭信号
    emit getQuited();
}

Menu::~Menu()
{
    delete startButton;
    delete quitButton;
    //delete helpButton;
    delete title;
}
