#include "selectvc.h"

#include <QDebug>
#include "mybutton.h"
#include <QMenuBar>

SelectVC::SelectVC(QWidget *parent) : WTMainWindow(parent)
{
    qDebug() << __func__;

    this->setWindowTitle("关卡选择");

//    this->parent()->

    MyButton * btn = new MyButton(":/res/BackButton.png",":/res/BackButtonSelected.png", this);
    btn->resize(72,32);
    connect(btn, &QPushButton::clicked, this, &SelectVC::wtBackBtnClicked);


    btn->move(this->width() - btn->width(),
              this->height() - btn->height());
}

void SelectVC::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // 搬动画家到QMenuBar 下面开始画, 主要是针对windows, mac电脑并没有差别
    painter.translate(0, this->menuBar()->height());


    QPixmap pix(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(), this->height(), pix);

    // 再加载一张标题logo图片

    pix.load(":/res/Title.png");
    painter.drawPixmap(30,0, pix);
}
