#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // 注释掉的话, 就什么都没有了, ui文件里面的都不会加载了
    // 关联ui文件到程序界面
    ui->setupUi(this);

    // 往状态栏添加信息
    ui->statusBar->addWidget(new QLabel("左侧信息", this));

    // 使用图片资源
    // 1. 使用绝对路径
//    ui->actionnew->setIcon( QIcon("/Users/codew/Desktop/qt/resource/images/addDeviceIcon.png") );

    // 2. 使用资源文件
    // 使用资源文件的路径形式
    // 冒号: + 前缀 / + 目录文件名
    /*
    这种方式缺点是占用内存, 视频什么的就用相对对路径吧~
    */
    ui->actionnew->setIcon( QIcon(":/Image/Luffy.png") );
}

MainWindow::~MainWindow()
{
    delete ui;
}
