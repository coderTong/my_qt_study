#include "xywidget.h"
#include <QApplication>

#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XYWidget w;


    // 1. 添加按钮
//    QPushButton btn;
//    btn.setText("快点你爸爸");
//    btn.show();

    // 2. 建立父子关系
    QPushButton btn;
    btn.setText("快点你爸爸");
    btn.setParent(&w);


    // 3. 构造函数传参
    QPushButton btn2("来啊傻逼", &w);
    btn2.move(100, 100);
    btn2.resize(200,200);


    // 4. 和按钮2建立父子关系
    QPushButton btn3("谁怕谁", &btn2);


    // 创建窗口标题
    w.setWindowTitle("你瞅啥!");

    // 设置窗口的固定大小
//    w.setFixedSize(800, 800);

    // 同时设置窗口对的位置和大小
    w.setGeometry(20,120,500, 500);





    w.show();

    return a.exec();
}
