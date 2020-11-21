#include "mybutton.h"

#include <QPropertyAnimation>

MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{

}

void MyButton::moveDown()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry", this);
    animation->setStartValue( this->geometry() );
    animation->setEndValue( QRect( this->x(),
                                   this->y() + 10,
                                   this->width(),
                                   this->height())  );
    // 100毫秒
    animation->setDuration(100);
    animation->start( QAbstractAnimation::DeleteWhenStopped );
}

void MyButton::moveUp()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry", this);
    animation->setStartValue( this->geometry() );
    animation->setEndValue( QRect( this->x(),
                                   this->y() - 10,
                                   this->width(),
                                   this->height())  );
    // 100毫秒
    animation->setDuration(100);
    animation->start( QAbstractAnimation::DeleteWhenStopped );
}

void MyButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QPixmap pix(":/res/MenuSceneStartButton.png");
    painter.drawPixmap(0,0,this->width(), this->height(), pix);

}
