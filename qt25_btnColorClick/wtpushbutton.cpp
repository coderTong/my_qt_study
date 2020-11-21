#include "wtpushbutton.h"

#include <QPainter>
#include <QBrush>
#include <QMouseEvent>

WTPushButton::WTPushButton(QWidget *parent) : QPushButton(parent)
{

}

void WTPushButton::paintEvent(QPaintEvent *e)
{


    QPainter painter(this);


    // 搞个画刷画背景颜色

    QBrush brush;
    brush.setStyle( Qt::SolidPattern );

//    brush.setColor(Qt::white);

    // 根据状态画背景

    switch (mStat) {

    case Normal:
        brush.setColor(Qt::red);
        break;

    case Entered:
        brush.setColor(Qt::green);
        break;

    case Pressed:
        brush.setColor(Qt::blue);
        break;
    }

    painter.setBrush(brush);

    // 画个圆试试
    // 减一是因为圆的某部分会被遮掉
    painter.drawEllipse(0, 0, this->width() - 1, this->height() - 1);

    // 画按钮的文字
    painter.drawText(0, 0, this->width(), this->height(),
                     Qt::AlignHCenter | Qt::AlignCenter, this->text());


}

void WTPushButton::enterEvent(QEvent *event)
{
    this->mStat = Entered;
    update();

}

void WTPushButton::leaveEvent(QEvent *event)
{
    this->mStat = Normal;
    update();
}

void WTPushButton::mousePressEvent(QMouseEvent *e)
{
    //将状态设置Pressed，只有左键才触发
        if(e->button()!=Qt::LeftButton)
            return;
    this->mStat = Pressed;
    update();

    // 信号依赖于事件
    QPushButton::mousePressEvent(e);
}

void WTPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    //将状态设置Entered，只有左键才触发
        if(e->button()!=Qt::LeftButton)
            return;
    this->mStat = Entered;
    update();

    QPushButton::mouseReleaseEvent(e);
}
