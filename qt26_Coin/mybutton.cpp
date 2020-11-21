#include "mybutton.h"

#include <QPropertyAnimation>

//MyButton::MyButton(QWidget *parent) : QPushButton(parent)
//{

//}

MyButton::MyButton(QString normalImage, QString pressedImage, QWidget *parent)
    : QPushButton(parent),
      mNormalImage(normalImage),
      mPressedImage(pressedImage)


{
    mState = Normal;
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

    //QPixmap pix(":/res/MenuSceneStartButton.png");
//    QPixmap pix(mNormalImage);

    QPixmap pix;
    if (mState == Normal){

        pix.load(mNormalImage);
    }

    if (mState == Pressed){

        pix.load(mPressedImage);
    }


    painter.drawPixmap(0,0,this->width(), this->height(), pix);

    // 画文字

    painter.drawText(0,
                     0,
                     this->width(),
                     this->height(),
                     Qt::AlignHCenter | Qt::AlignVCenter,
                     this->text());

}

// 鼠标按下
void MyButton::mousePressEvent(QMouseEvent *event)
{
    this->mState = Pressed;
    update();

    // 保证信号槽功能
    QPushButton::mousePressEvent(event);
}

// 鼠标松开
void MyButton::mouseReleaseEvent(QMouseEvent *event)
{
    this->mState = Normal;
    update();

    // 保证信号槽功能
    QPushButton::mouseReleaseEvent(event);
}
