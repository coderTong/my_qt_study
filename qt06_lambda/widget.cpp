#include "widget.h"

#include <QPushButton>

#include <QtDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    // lambda表示

    void (*p)()= [](){
        qDebug() << "hellow lambda";
    };
    p();

    // 局部变量捕获
    int a = 10;
    int b = 20;
    int c = 20;
    int d = 20;
    int e = 20;
    int f = 20;


    [=](){

        qDebug() << "你大爷!";
        qDebug() << a << b;
    }();

    QPushButton * btn = new QPushButton("滚一边去", this);
    connect(btn, &QPushButton::clicked, [=](){

        qDebug() << "滚你大爷!";
    });

}

Widget::~Widget()
{

}
