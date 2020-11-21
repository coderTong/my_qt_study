#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    mTimerId(0),
    mTimerId2(0)
{
    ui->setupUi(this);


}

Widget::~Widget()
{
    delete ui;
}

void Widget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == this->mTimerId)
    {
        static int num = 1;

        this->ui->lcdNumber->display(num++);
    }

    if (event->timerId() == this->mTimerId2)
    {
        static int num2 = 1;

        this->ui->lcdNumber2->display(num2++);
    }

}

void Widget::on_pushButton_clicked()
{
    // 1000代表秒
    this->mTimerId = startTimer(1000);


}

void Widget::on_pushButton_2_clicked()
{
    killTimer(this->mTimerId);
    this->mTimerId = 0;
}

void Widget::on_pushButton_4_clicked()
{
    // start
    this->mTimerId2 = startTimer(100);
}

void Widget::on_pushButton_3_clicked()
{
    // stop
    killTimer(this->mTimerId2);
    this->mTimerId2 = 0;
}
