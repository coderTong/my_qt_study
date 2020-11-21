#include "playvc.h"
#include "mybutton.h"
#include <QDebug>
#include <QMenuBar>
#include <QLabel>

PlayVC::PlayVC(int level, QWidget *parent) : WTMainWindow(parent)
{
    MyButton * btn = new MyButton(":/res/BackButton.png",":/res/BackButtonSelected.png", this);
    btn->resize(72,32);
    connect(btn, &QPushButton::clicked, this, &PlayVC::wtBackBtnClicked);


    btn->move(this->width() - btn->width(),
              this->height() - btn->height());


    // 添加左下角的label
    QLabel *label = new QLabel(this);
    label->resize(150, 50);
    label->setText( QString("Level: %1").arg(level) );
    // 设置字体
    label->setFont( QFont("华文新魏", 20) );
    label->move(30, this->height() - label->height());


}


PlayVC::~PlayVC()
{
    qDebug() << __func__;
}

void PlayVC::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // 搬动画家到QMenuBar 下面开始画, 主要是针对windows, mac电脑并没有差别
    painter.translate(0, this->menuBar()->height());


    QPixmap pix(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(), this->height(), pix);

    // 再加载一张标题logo图片

    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()/2, pix.height()/2);

    painter.drawPixmap(10,0, pix);
}


