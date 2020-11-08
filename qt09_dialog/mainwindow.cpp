#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDialog>
#include <QDebug>

#include <QCloseEvent>
#include "myqdialog.h"

#include <QMessageBox>

#include <QFileDialog>

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
//        qDebug() << "一念永恒, 白小纯sb";

        // 用new的话就不会
//        QDialog *dlg = new QDialog(this);
//        // 释放问题只有父对象释放他才会被释放, 我需要它关闭就释放
//        // 通过设置窗口的属性, 让他关闭的时候自动释放
//        dlg->setAttribute(Qt::WA_DeleteOnClose);

//        // 非modal
//        dlg->show();
//        qDebug() << "一念永恒, 白小纯sb";



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
//            qDebug() << "一念永恒, 白小纯sb一样~";

//            this->dlg = dlg;


            // 用new的话就不会
            MyQDialog *dlg = new MyQDialog(this);
            // 释放问题只有父对象释放他才会被释放, 我需要它关闭就释放
            // 通过设置窗口的属性, 让他关闭的时候自动释放
            dlg->setAttribute(Qt::WA_DeleteOnClose);


//            connect(dlg, &QDialog::closeEvent, this, &MainWindow::deallocDialog);

            // 非modal
            dlg->show();
            qDebug() << "一念永恒, 白小纯sb一样~";

            this->dlg = dlg;
        }

    });

}

MainWindow::~MainWindow()
{
    qDebug() << __func__;

    delete ui;
}


void MainWindow::test01()
{
    qDebug() << __func__;
    this->dlg = NULL;
}

void MainWindow::on_actionCritical_triggered()
{
    QMessageBox::critical(this, "错误", "可恶中国每个地方素来都有一两样让其闻名全国的美食，比如沙县的小吃、兰州的牛肉面、重庆的火锅、柳州的螺蛳粉、天津的煎饼果子……但真正到过当地的人才会知道，那些地方的美味潜藏在当地每一户普通家庭的饭桌之上，藏匿于老城区的菜市场之中。!");
}

void MainWindow::on_actionWarning_triggered()
{
    QMessageBox::warning(this, "警告", "小心手抓饼出没~");
}

void MainWindow::on_actioninfo_triggered()
{
    QMessageBox::information(this, "信息", "你要还花呗了~");
}

void MainWindow::on_actionQuestion_triggered()
{
    if ( QMessageBox::Ok == QMessageBox::question(this, "吃饭","你确定要做全栈吗?", QMessageBox::Cancel|QMessageBox::Ok) ){

        qDebug("ok");
    }else {

        qDebug("Cancel");
    }
}

void MainWindow::on_actionQFileDialog_triggered()
{
    // 文件对话框

    // 跳转到了二进制目录
//    QFileDialog::getOpenFileName(this, "打开一个文件");


    // 指定打开的目录
   // QFileDialog::getOpenFileName(this, "打开一个文件","/");

    // 指定打开的目录 + 文件过滤器

    QString fileName = QFileDialog::getOpenFileName(this,
                                 "打开一个文件",
                                 "/",
                                 "PNG (*.png) ;; JPG (*.jpg) ;; GIF (*.gif) ;; all (*.*) ;;");


    qDebug() << fileName;
}










