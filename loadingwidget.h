#ifndef LOADINGWIDGET_H
#define LOADINGWIDGET_H

#include <QWidget>
#include <QMovie>
#include <QLabel>
#include <QBoxLayout>
#include <QFont>
#include "param.h"

class LoadingWidget: public QWidget
{
    Q_OBJECT
public:
    LoadingWidget(QWidget *parent = 0);
    void Loading(); // 展示
private:
    QMovie *gif; // 动图
    QLabel lab_text, lab_gif; // 字符
signals:
    void timeOver(); // 发出结束的信号
};

#endif // LOADINGWIDGET_H
