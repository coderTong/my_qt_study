#include "widget.h"

#include <QPushButton>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    this->resize(500, 400);
    this->setWindowTitle("窗口1");

    QPushButton *btn = new QPushButton("按钮1", this);


    widget2 = new MyWidget;
    connect(btn, &QPushButton::clicked, [=](){

        // 2显示, 1隐藏
        widget2->show();
//        this->hide();
    });


    connect( widget2, &MyWidget::myBtn2Clicked, [=](){

        this->show();
//        widget2->hide();
    });

}

Widget::~Widget()
{
    delete widget2;
}
