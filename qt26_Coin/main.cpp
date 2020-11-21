#include "wtmainwindow.h"
#include <QApplication>

#include "startvc.h"
#include "selectvc.h"





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    WTMainWindow w;
//    w.show();

    StartVC sVC;
    sVC.show();

//    SelectVC sVC;
//    sVC.show();

    return a.exec();
}
