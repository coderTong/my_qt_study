#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
//    system("ffmpeg -v");

    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
