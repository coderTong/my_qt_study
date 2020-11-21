#include "coinbutton.h"
#include <QPainter>

CoinButton::CoinButton(QWidget *parent) : QPushButton(parent)
{
    // 初始状态
    this->setState(0);
    //设置按钮不规则样式，去掉边框
    this->setStyleSheet("QPushButton{border:0px;}");


    connect(&this->mTimer, &QTimer::timeout, [=](){

        if (this->mState){

            // 银币翻转金币
            this->mFrame--;

            QString imagePath = QString(":/res/Coin000%1.png").arg(this->mFrame);
            this->setIcon( QIcon(imagePath) );

            if (this->mFrame == 1){

                this->mTimer.stop();
            }

        }else {
            // 金币翻转银币
            this->mFrame++;

            QString imagePath = QString(":/res/Coin000%1.png").arg(this->mFrame);
            this->setIcon( QIcon(imagePath) );

            if (this->mFrame == 8){

                this->mTimer.stop();
            }
        }

    });
}

int CoinButton::state() const
{
    return mState;
}

void CoinButton::setState(int state)
{
    mState = state;
    if (this->mState)
    {
        // 1就是金币
        this->setIcon( QIcon(":/res/Coin0001.png") );
    }else{

        // 0 就是银币
        this->setIcon( QIcon(":/res/Coin0008.png") );
    }

    this->setIconSize(this->size());
}
// 0--->1   1
// 1--->0   0
void CoinButton::setStateWithAnimation(int state)
{
    mState = state;

    if (mState){

        // mState == 1 表示银币翻转金币

        this->mFrame = 8;

    }else {

        // mState == 0 表示金币翻转银币
        this->mFrame = 1;
    }

    // 100毫秒(0.1秒) 换一帧
    this->mTimer.start(100);

}

void CoinButton::flip()
{
//    this->mState = !this->mState;
//    this->setState(this->mState);

    this->setStateWithAnimation(!this->mState);
}

void CoinButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QPixmap pix(":/res/BoardNode.png");

    painter.drawPixmap(0,0,this->width(), this->height(), pix);

    QPushButton::paintEvent(event);
}
