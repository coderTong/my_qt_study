#include "wtmainwindow.h"
#include "ui_wtmainwindow.h"

#include <QDebug>

WTMainWindow::WTMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WTMainWindow)
{

    qDebug() << __func__;

    ui->setupUi(this);

    // 窗口标题
    this->setWindowTitle("翻金币");
    // 窗口图片
    this->setWindowIcon( QIcon(":/res/Coin0001.png") );
    // 固定大小
    this->setFixedSize(320, 588);

}

WTMainWindow::~WTMainWindow()
{
    delete ui;
}

void WTMainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QPixmap pix(":/res/MenuSceneBg.png");
    painter.drawPixmap(0,0,this->width(), this->height(), pix);
}
