#include "tomwidget.h"
#include <QApplication>

#include <QDebug>

int main(int argc, char *argv[])
{

    //创建一个应用程序对象
    //维护qt应用程序生命的一个对象，每个qt有且仅有一个的对象
    //  iOS也有类似的  UIApplicationMain
    QApplication a(argc, argv);
    //  窗口类的一个对象
    TomWidget w;
    w.show();

    qDebug() << "吃饭了没";

    return a.exec();
}
