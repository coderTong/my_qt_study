#include "mywidget.h"

#include <QPushButton>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{

    resize(800, 600);

    QPushButton * btn2 = new QPushButton("按钮2", this);

    connect(btn2, &QPushButton::clicked, [=](){

        emit this->myBtn2Clicked();
    });

}
