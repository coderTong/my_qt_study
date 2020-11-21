#include "selectvc.h"

#include <QDebug>
#include "mybutton.h"
#include <QMenuBar>
#include "playvc.h"

SelectVC::SelectVC(QWidget *parent) : WTMainWindow(parent)
{
    qDebug() << __func__;

    this->setWindowTitle("关卡选择");

//    this->parent()->

    MyButton * btn = new MyButton(":/res/BackButton.png",":/res/BackButtonSelected.png", this);
    btn->resize(72,32);
    connect(btn, &QPushButton::clicked, this, &SelectVC::wtBackBtnClicked);


    btn->move(this->width() - btn->width(),
              this->height() - btn->height());



    // 关卡按钮20个
    const int colWidth = 70;
    const int rowHeight = 70;

    // x, y 偏移
    const int offsetX = 25;
    const int offsetY = 130;

    for (int i = 0; i < 20; i++) {

        MyButton * btn = new MyButton(":/res/LevelIcon.png",":/res/LevelIcon.png", this);
        btn->setText(QString::number(i+1));

        // 排列
        // 行 i / 4
        // 列 i % 4

        int row = i / 4;
        int col = i % 4;

        // x 坐标 = 列数 * 列宽 + x偏移
        // y 坐标 = 行数 * 行高 + y偏移

        int x = col * colWidth + offsetX;
        int y = row * rowHeight + offsetY;

        btn->resize(57,57);
        btn->move(x,y);

        connect(btn, &MyButton::clicked, [=](){

            PlayVC * pVC = new PlayVC(i+1);
            // 设置关闭的时候释放
            pVC->setAttribute(Qt::WA_DeleteOnClose);
            pVC->show();
            this->hide();

            connect(pVC, &PlayVC::wtBackBtnClicked, [=](){

                this->show();
                pVC->close();
            });

        });

    }
}

void SelectVC::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // 搬动画家到QMenuBar 下面开始画, 主要是针对windows, mac电脑并没有差别
    painter.translate(0, this->menuBar()->height());


    QPixmap pix(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(), this->height(), pix);

    // 再加载一张标题logo图片

    pix.load(":/res/Title.png");
    painter.drawPixmap(30,0, pix);
}
