#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    av_register_all();


    qDebug() << avcodec_configuration();
    unsigned version = avcodec_version();
    QString ch = QString::number(version);
    qDebug() << "version:" << version;
}

MainWindow::~MainWindow()
{
    delete ui;
}
