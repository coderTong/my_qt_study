#include "widget.h"
#include "ui_widget.h"

#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    mPox = 0;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    // painter绘制已经存在的图片

    QPainter painter(this);
    QPixmap pixmap(":/Image/Luffy.png");
    painter.drawPixmap(mPox, 0, pixmap);
}

void Widget::on_pushButton_clicked()
{

    // 每点击一次就向右移动 10像素

    mPox += 10;

    // 这个方法会立刻刷新
//    this->repaint();

    // 这个方法会做些优化, 比repaint这个方法可能慢点
    this->update();

}
