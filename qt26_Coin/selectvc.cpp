#include "selectvc.h"

#include <QDebug>

SelectVC::SelectVC(QWidget *parent) : WTMainWindow(parent)
{
    qDebug() << __func__;

    this->setWindowTitle("关卡选择");

//    this->parent()->

    QPushButton * btn = new QPushButton("返回", this);

    connect(btn, &QPushButton::clicked, this, &SelectVC::wtBackBtnClicked);


    btn->move(this->width() - btn->width(),
              this->height() - btn->height());
}
