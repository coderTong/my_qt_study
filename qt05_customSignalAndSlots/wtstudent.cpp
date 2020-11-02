#include "wtstudent.h"
#include <QDebug>

WtStudent::WtStudent(QObject *parent) : QObject(parent)
{

}

void WtStudent::treat()
{
    qDebug() << "jjjjj吃翔不?";
}

void WtStudent::treat(QString foot)
{
    //你要吃啥! 答:  "黄焖鸡"
    //qDebug() << "你要吃啥! 答: " << foot;


    // 1. QString 转成 char *
    // 你要吃啥! 答:  黄焖鸡
//    qDebug() << "你要吃啥! 答: " << foot.toUtf8().data();

    // 2.你要吃啥! 答:  黄焖鸡
    qDebug().noquote() << "你要吃啥! 答: " << foot;
}
