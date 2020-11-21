#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //  画家偏移
    painter.translate(100, 0);


    // =============================================
    // 创建一支画笔
    QPen pen;
    pen.setColor( QColor(255, 0, 0) );
    // 设置笔宽
    pen.setWidth(3);
    // 设置画笔的风格
    pen.setStyle( Qt::DashDotDotLine );
    painter.setPen(pen);
   // =============================================


    // =============================================
    // 需要填充, 使用画刷
    QBrush brush;
    brush.setColor(Qt::cyan);
    // 默认情况下, 画刷不填充, 还得设置风格
    brush.setStyle(Qt::Dense4Pattern);
    painter.setBrush(brush);
    // =============================================


    // 画个矩形
    painter.drawRect(20, 20, 50, 50);
    // 画一条线
    painter.drawLine(0,0,100, 100);
    // 画圆形, 使用椭圆
    painter.drawEllipse( QPoint(100, 100), 50, 50 );
    // 画文字
    painter.drawText(200, 100, "好好学习, 赚钱养家");
}


