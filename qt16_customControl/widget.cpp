#include "widget.h"
#include "ui_widget.h"

#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 勾上就用<> , 不勾选就用""



}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    // 获取值

    QString value = QString::number(this->ui->customView->valueMy());

    QMessageBox::information(this, "值", value);
}

void Widget::on_pushButton_2_clicked()
{
    ui->customView->setMyValue(50);
}
