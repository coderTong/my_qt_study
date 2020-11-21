#include "mylabel.h"
#include <QMouseEvent>

#include <QDebug>

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    this->installEventFilter(this);
}

void MyLabel::mousePressEvent(QMouseEvent *ev)
{
    qDebug() << __func__;

    Qt::MouseButton btn = ev->button();
    QString strButton = "";

    if ( btn == Qt::LeftButton ){

        strButton = "LeftButton";
    }

    if ( btn == Qt::RightButton ){

        strButton = "RightButton";
    }


    if ( btn == Qt::MidButton ){

        strButton = "MidButton";
    }



    int x = ev->x();
    int y = ev->y();

    qDebug() << x << y;

    QString str = QString("[%1, %2, %3] PressEvent")
            .arg(x)
            .arg(y)
            .arg(strButton);
    this->setText(str);
}

void MyLabel::mouseMoveEvent(QMouseEvent *ev)
{

    qDebug() << __func__;


    Qt::MouseButtons btn = ev->buttons();
    QString strButton = "";

    if ( btn & Qt::LeftButton ){

        strButton += "LeftButton";
    }

    if ( btn & Qt::RightButton ){

        strButton += "RightButton";
    }


    if ( btn & Qt::MidButton ){

        strButton += "MidButton";
    }



    int x = ev->x();
    int y = ev->y();

    qDebug() << x << y;

    QString str = QString("[%1, %2, %3] MoveEvent")
            .arg(x)
            .arg(y)
            .arg(strButton);
    this->setText(str);
}

bool MyLabel::event(QEvent *event)
{

    // 调用父类

//    qDebug() << __func__;

    if (event->type() == QEvent::MouseMove)
    {

        qDebug() << "QEvent::MouseMove";

//        this->mouseMoveEvent( static_cast<QMouseEvent *>(event) );

        return false;
    }

    return QLabel::event(event);
}

bool MyLabel::eventFilter(QObject *watched, QEvent *event)
{
    // 如果返回的false代表不拦截,  true 就是要拦截

   if ( event->type() == QEvent::MouseMove )
   {

       return false;
   }

   return false;
}
