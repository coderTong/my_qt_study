#include "playvc.h"
#include "mybutton.h"
#include <QDebug>
#include <QMenuBar>
#include <QLabel>
#include <QTimer>
#include "dataconfig.h"

#include <QMessageBox>

#include <QLabel>
#include <QPropertyAnimation>

PlayVC::PlayVC(int level, QWidget *parent) : WTMainWindow(parent)
{
    MyButton * btn = new MyButton(":/res/BackButton.png",":/res/BackButtonSelected.png", this);
    btn->resize(72,32);
    connect(btn, &QPushButton::clicked, this, &PlayVC::wtBackBtnClicked);


    btn->move(this->width() - btn->width(),
              this->height() - btn->height());


    // 添加左下角的label
    QLabel *label = new QLabel(this);
    label->resize(150, 50);
    label->setText( QString("Level: %1").arg(level) );
    // 设置字体
    label->setFont( QFont("华文新魏", 20) );
    label->move(30, this->height() - label->height());

    dataConfig data;
    QVector < QVector<int>> dataArray = data.mData[level];

    // 16个硬币按钮
    // 关卡按钮20个
    const int colWidth = 50;
    const int rowHeight = 75;
    // x, y 偏移
    const int offsetX = 57;
    const int offsetY = 200;

    for (int row = 0; row < 4; row++) {

        for (int col = 0; col < 4; col++) {

            // x 坐标 = 列数 * 列宽 + x偏移
            // y 坐标 = 行数 * 行高 + y偏移

            int x = col * colWidth + offsetX;
            int y = row * rowHeight + offsetY;

            //
           CoinButton *btn = new CoinButton(this);
           // 存储
           mCoins[row][col] = btn;

           // move + resize 就等iOS setFrame
           btn->setGeometry(x,y,50,50);
           btn->setState(dataArray[row][col]);


           connect(btn, &QPushButton::clicked, [=](){

               //btn->flip();

               this->flip(row, col);

           });
        }
    }

}


PlayVC::~PlayVC()
{
    qDebug() << __func__;
}

void PlayVC::flip(int row, int col)
{
    this->mCoins[row][col]->flip();

    // 翻动上下左右的硬币
    QTimer::singleShot(250, [=](){
        // 下
        if(row+1 < 4)
        {
            this->mCoins[row+1][col]->flip();
        }

        // 上
        if(row-1 >= 0)
        {
            this->mCoins[row-1][col]->flip();
        }

        // 左
        if (col - 1 >= 0)
        {
            this->mCoins[row][col-1]->flip();
        }

        // 右
        if (col + 1 < 4)
        {
            this->mCoins[row][col+1]->flip();
        }

        // 判断游戏硬币是否胜利
        this->judgeWin();
    });



}

void PlayVC::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // 搬动画家到QMenuBar 下面开始画, 主要是针对windows, mac电脑并没有差别
    painter.translate(0, this->menuBar()->height());


    QPixmap pix(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(), this->height(), pix);

    // 再加载一张标题logo图片

    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()/2, pix.height()/2);

    painter.drawPixmap(10,0, pix);
}

void PlayVC::judgeWin()
{
    // 判断状态都是1
    for (int row = 0; row < 4; row++) {

        for (int col = 0; col < 4; col++) {

            // 只要有一个是银币就游戏继续
            if (!this->mCoins[row][col]->state())
            {
                return;
            }
        }
    }

    // 到这一步, 所有都是金币了
//    QMessageBox::information(this, "恭喜","你已经胜利了!");

    QLabel *labelWin = new QLabel(this);

    QPixmap pix = QPixmap(":/res/LevelCompletedDialogBg.png");

    labelWin->setPixmap( pix);
    labelWin->resize(pix.size());
    labelWin->show();

    labelWin->move( (this->width() - labelWin->width())/2, -labelWin->height()  );

    QPropertyAnimation * animation = new QPropertyAnimation(labelWin, "geometry", this);
    animation->setStartValue(labelWin->geometry());
    animation->setEndValue( QRect(labelWin->x(),
                                  labelWin->y() + 100,
                                  labelWin->width(),
                                  labelWin->height()) );
    animation->setDuration(500);
    // 设置动画的运动曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //
    animation->start( QAbstractAnimation::DeleteWhenStopped );
}


