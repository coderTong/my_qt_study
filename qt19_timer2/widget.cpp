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

void Widget::on_pushButton_clicked()
{
    this->myTimer = new QTimer(this);
    connect(this->myTimer, &QTimer::timeout, [=](){
        static int num = 1;
        this->ui->lcdNumber->display(num++);
    });

    // 10毫秒搞一次
    this->myTimer->start(10);
}

void Widget::on_pushButton_2_clicked()
{
    this->myTimer->stop();
    this->myTimer = NULL;
}
