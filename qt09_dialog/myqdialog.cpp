#include "myqdialog.h"
#include "mainwindow.h"
#include <QDebug>

MyQDialog::MyQDialog(QWidget *parent) : QDialog(parent)
{

}


void MyQDialog::closeEvent(QCloseEvent *event)
{
    qDebug() << "来了~~~~~~";

    MainWindow *man =  (MainWindow *)this->parent();
    man->test01();
}
