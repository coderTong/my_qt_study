#include "mainwindow.h"
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(800, 600);

    // 菜单栏, 获取当前窗口的菜单栏, 没有的话 会自动创建一个
    QMenuBar *menuBar = this->menuBar();

    // 添加菜单栏
    QMenu *menu1 = menuBar->addMenu("文件");
    QMenu *menu2 = menuBar->addMenu("编辑");

    // 到这一步mac才会显示, 上面哪一步, 不会显示
    QAction * actionNew = menu1->addAction("ccc1");
    menu1->addAction("ccc2");
    menu1->addAction("ccc3");
    menu1->addSeparator();
    menu1->addAction("ccc4");
    QAction * actionOpen = menu2->addAction("ccc2");

    /*
      这个是addAction和addMenu这个之间写才可以
    */
    menu1->addSeparator();
    // 添加二级菜单
    QMenu *menuRecent = menu1->addMenu("最近打开的文件");
    menuRecent->addAction("1.txt");
    menuRecent->addAction("2.txt");
    menuRecent->addAction("3.txt");




}

MainWindow::~MainWindow()
{

}
