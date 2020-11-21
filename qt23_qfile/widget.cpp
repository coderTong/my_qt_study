#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QDebug>
#include <QFile>

#include <QTextCodec>
#include <QFileInfo>

#include <QDateTime>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QFile file("/Users/codew/Desktop/qt/file/cc.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    file.write("hi~");
    file.close();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_myBtn_clicked()
{
    this->readFileTxtAllAndCodec();
}

/*
 * 默认utf-8
*/
void Widget::readFileTxtAll()
{
    /*
     * 第三个参数是默认地址
    */
    QString fileName = QFileDialog::getOpenFileName(this, "打开一个txt", "/Users/codew/Desktop/qt/file", "TXT (*.txt)");


    // 对 fileName 做个判断, 如果没有选择文件, 就是一个空

    if ( fileName.isEmpty() ){

        qDebug() << "并没有选择某个文件";

        return;
    }

    qDebug() << "选择了文件: " << fileName;

    // 填到输入框
    this->ui->lineEdit->setText(fileName);

    // 使用qfile 来读取文件
    QFile file(fileName);

    // 打开文件
    file.open(QIODevice::ReadOnly);

    QByteArray array;

    // 全部一哈读出来
    array = file.readAll();


    // 这个是单行
//    do{

//        array += file.readLine();
//    }while ( !file.atEnd() );


    QString content = QString(array);

    this->ui->plainTextEdit->setPlainText(content);

    file.close();
}


/*
 * 默认utf-8
*/
void Widget::readFileTxtSingleline()
{
    /*
     * 第三个参数是默认地址
    */
    QString fileName = QFileDialog::getOpenFileName(this, "打开一个txt", "/Users/codew/Desktop/qt/file", "TXT (*.txt)");


    // 对 fileName 做个判断, 如果没有选择文件, 就是一个空

    if ( fileName.isEmpty() ){

        qDebug() << "并没有选择某个文件";

        return;
    }

    qDebug() << "选择了文件: " << fileName;

    // 填到输入框
    this->ui->lineEdit->setText(fileName);

    // 使用qfile 来读取文件
    QFile file(fileName);

    // 打开文件
    file.open(QIODevice::ReadOnly);

    QByteArray array;

    // 我就读一行
    //array = file.readLine();

    // 用读行的方式一哈读出来
    do{

        array += file.readLine();
    }while ( !file.atEnd() );


    QString content = QString(array);

    this->ui->plainTextEdit->setPlainText(content);

    file.close();
}

void Widget::readFileTxtAllAndCodec()
{
    /*
     * 第三个参数是默认地址
    */
    QString fileName = QFileDialog::getOpenFileName(this, "打开一个txt", "/Users/codew/Desktop/qt/file", "TXT (*.txt)");


    // 对 fileName 做个判断, 如果没有选择文件, 就是一个空

    if ( fileName.isEmpty() ){

        qDebug() << "并没有选择某个文件";

        return;
    }

    qDebug() << "选择了文件: " << fileName;

    // 填到输入框
    this->ui->lineEdit->setText(fileName);

    // 使用qfile 来读取文件
    QFile file(fileName);

    // 打开文件
    file.open(QIODevice::ReadOnly);

    QByteArray array;

    // 我就读一行
    //array = file.readLine();

    // 用读行的方式一哈读出来
    do{

        array += file.readLine();
    }while ( !file.atEnd() );


    QTextCodec *codec = QTextCodec::codecForName("gbk");
    QString content = codec->toUnicode(array);
    this->ui->plainTextEdit->setPlainText(content);


    QFileInfo info(fileName);


    qDebug() << "文件全名:    " << info.fileName();
    qDebug() << "baseName:   " << info.baseName();
    qDebug() << "创建时间:    " << info.created().toString("yyyy-mm-dd");
    qDebug() << "最后修改时间: " <<info.lastModified();


    file.close();
}



