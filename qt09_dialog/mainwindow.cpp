#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDialog>
#include <QDebug>

#include <QCloseEvent>
#include "myqdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionModal, &QAction::triggered, [=](){



        QDialog dlg(this);
        // 消息循环,  阻塞
        dlg.exec();

        // 关闭 QDialog 才会打印
        qDebug() << "一念永恒, 白小纯sb一样~";
    });

    connect(ui->actionNoModal, &QAction::triggered, [=](){

        /*

          局部变量, 一下就没有了, 根本看不到
         show是非阻塞, 所以局部变量dlg马上就会被释放
        */

//        QDialog dlg(this);
//        // 非modal
//        dlg.show();
//        qDebug() << "一念永恒, 白小纯sb一样~, 让他死吧~";

        // 用new的话就不会
//        QDialog *dlg = new QDialog(this);
//        // 释放问题只有父对象释放他才会被释放, 我需要它关闭就释放
//        // 通过设置窗口的属性, 让他关闭的时候自动释放
//        dlg->setAttribute(Qt::WA_DeleteOnClose);

//        // 非modal
//        dlg->show();
//        qDebug() << "一念永恒, 白小纯sb一样~, 让他死吧~";



        if (this->dlg){

            qDebug() << "已经存在了";
            return ;

        }else {

//            // 用new的话就不会
//            QDialog *dlg = new QDialog(this);
//            // 释放问题只有父对象释放他才会被释放, 我需要它关闭就释放
//            // 通过设置窗口的属性, 让他关闭的时候自动释放
//            dlg->setAttribute(Qt::WA_DeleteOnClose);


//            connect(dlg, &QDialog::closeEvent, this, &MainWindow::deallocDialog);

//            // 非modal
//            dlg->show();
//            qDebug() << "一念永恒, 白小纯sb一样~, 让他死吧~";

//            this->dlg = dlg;


            // 用new的话就不会
            MyQDialog *dlg = new MyQDialog(this);
            // 释放问题只有父对象释放他才会被释放, 我需要它关闭就释放
            // 通过设置窗口的属性, 让他关闭的时候自动释放
            dlg->setAttribute(Qt::WA_DeleteOnClose);


//            connect(dlg, &QDialog::closeEvent, this, &MainWindow::deallocDialog);

            // 非modal
            dlg->show();
            qDebug() << "一念永恒, 白小纯sb一样~, 让他死吧~";

            this->dlg = dlg;
        }

    });

}

MainWindow::~MainWindow()
{
    qDebug() << __func__;

    delete ui;
}

void MainWindow::deallocDialog()
{

    qDebug() << "真的进了了";
    this->dlg = NULL;
}

void MainWindow::test01()
{
    qDebug() << __func__;
    this->dlg = NULL;
}
