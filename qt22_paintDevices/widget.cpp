#include "widget.h"
#include "ui_widget.h"

#include <QPainter>

#include <QPicture>

#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // ==========================================
    // Pixmap  作为绘图设备
//    QPixmap pix(300, 300);
//    pix.fill(Qt::black);
//    QPainter painter( &pix );
//    painter.setPen( QColor(255, 0, 0) );
//    painter.drawEllipse( QPoint(150, 150), 100, 100 );
//    pix.save( "/Users/codew/Desktop/qt/my_qt_study/qt22_paintDevices/test/pix.png" );


    // ==========================================
//    QImage img(300, 300, QImage::Format_RGB32);
//    img.fill(Qt::white);
//    QPainter painter( &img );
//    painter.setPen( QColor(255, 0, 0) );
//    painter.drawEllipse( QPoint(150, 150), 100, 100 );
//    img.save( "/Users/codew/Desktop/qt/my_qt_study/qt22_paintDevices/test/img.png" );


    // ==========================================
//    QPicture pic;
//    QPainter painter;
//    painter.begin( &pic );
//    painter.drawEllipse( QPoint(150, 150), 100, 100 );
//    painter.end();
//    pic.save( "/Users/codew/Desktop/qt/my_qt_study/qt22_paintDevices/test/pic.png" );

}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    // 先显示一张图片,  然后再改它的像素

    qDebug() << __func__;

//    QImage img;
//    img.load( ":/Image/Luffy.png" );

//    // 修改像素

//    for (int x = 50; x < 100; ++x) {

//        for (int y = 50; y < 100; y++) {

//            img.setPixelColor(x, y, QColor(0,255, 0));
//        }
//    }

//    QPainter painter(this);
//    painter.drawImage(0, 0, img);


    // 重现QPicture
    QPainter painter(this);
    QPicture pic;
    pic.load("/Users/codew/Desktop/qt/my_qt_study/qt22_paintDevices/test/pic.png");
    painter.drawPicture(0, 0, pic);

}
