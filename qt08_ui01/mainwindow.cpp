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
}

MainWindow::~MainWindow()
{
    delete ui;
}
