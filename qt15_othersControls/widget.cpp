#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

#include <QMovie>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


    QMovie * mo = new QMovie(":/Image/mario.gif", QByteArray(), this);
    ui->label->setMovie(mo);
    mo->start();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_35_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::on_pushButton_36_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Widget::on_comboBox_activated(int index)
{
    qDebug() << index;
}
