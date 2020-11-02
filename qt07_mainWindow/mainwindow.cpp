#include "mainwindow.h"
#include <QMenuBar>
#include <QToolBar>

#include <QLabel>
#include <QStatusBar>

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


    // 1. 工具栏, 可以有多个工具栏
    QToolBar * toolBar = this->addToolBar("");
    // 工具栏 添加工具
    toolBar->addAction(actionNew);
    toolBar->addAction(actionOpen);
    // 一上来就是左边, 但是还是可以到处拖动的
    this->addToolBar(Qt::LeftToolBarArea, toolBar);
    // 只能拖动停靠在左边或者右边
    toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);
    // 设置工具栏 不可以 浮动
    toolBar->setFloatable(false);
    // 设置工具栏 不允许 拖动
    toolBar->setMovable(false);


    // 状态栏, 只有一个
    // 获取窗口的状态栏
    QStatusBar *statusBar = this->statusBar();
    QLabel * leftLabel = new QLabel("左侧信息", this);
    QLabel * leftLabel2 = new QLabel("左侧信息2", this);
    QLabel * rightLabel = new QLabel("右侧信息", this);

    statusBar->addWidget(leftLabel);
    statusBar->addWidget(leftLabel2);
    statusBar->addPermanentWidget(rightLabel);

}

MainWindow::~MainWindow()
{

}
