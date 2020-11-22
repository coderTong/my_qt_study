#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "关于", "你来看大爷了~");
}

void MainWindow::on_toolButton_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_toolButton_2_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_toolButton_3_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_toolButton_4_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_toolButton_5_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_toolButton_6_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_pushButton_submit_clicked()
{
    // 提交表单

    QString content ;

    content += QString("你的名字: %1\n").arg(this->ui->lineEdit_name->text());


    content += QString("性别: %1\n").arg( this->ui->radioButton_male->isChecked() ? "男":"女" );

    content += QString("你的职业: %1\n").arg(this->ui->comboBox_job->currentText());
    content += QString("你的年龄: %1\n").arg(this->ui->spinBox_age->text());
    content += QString("你的生日: %1\n").arg(this->ui->dateTimeEdit_birthday->text());


    QString feel = "不错哟";

    if (this->ui->radioButton_likeGood->isChecked())
    {
        feel = "很喜欢";
    }else if (this->ui->radioButton_perfect ->isChecked()) {
        feel = "完美";
    }

    content += QString("你的感觉: %1\n").arg(feel);

    QMessageBox::information(this, "感谢提交", content);
}
