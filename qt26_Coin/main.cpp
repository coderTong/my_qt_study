#include "wtmainwindow.h"
#include <QApplication>

#include "startvc.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    WTMainWindow w;
//    w.show();

    StartVC sVC;
    sVC.show();

    return a.exec();
}
