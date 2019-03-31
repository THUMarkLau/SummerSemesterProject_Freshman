#include "loadingwidget.h"
#include <QDebug>
#include <QTimer>

LoadingWidget::LoadingWidget(QWidget *parent):
    QWidget(parent), gif(new QMovie)
{
    // TODO:设置大小形态，并且添加部件
    QVBoxLayout *vLayout = new QVBoxLayout;

    setFixedSize(1280, 720);
    setWindowFlag(Qt::FramelessWindowHint);

    gif->setFileName(IMAGE_LOADING);
    lab_gif.setMovie(gif);
    vLayout->addWidget(&lab_gif, 0, Qt::AlignCenter);

    QFont font;
    font.setPointSize(15);
    lab_text.setFont(font);
    lab_text.setText("Loading");
    vLayout->addWidget(&lab_text, 0, Qt::AlignCenter);

    setLayout(vLayout);
    hide();
//    connect(this, SIGNAL(timeOver()), this, SLOT(close()));
}

void LoadingWidget::Loading()
{
    // TODO:开始展示
    gif->start();
    this->show();
}
