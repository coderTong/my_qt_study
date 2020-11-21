#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_myBtn_pressed()
{
    this->ui->label->setText("鼠标按下");
}

void Widget::on_myBtn_released()
{
    this->ui->label->setText("鼠标松开");
}
