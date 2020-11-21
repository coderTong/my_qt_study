#include "coinbutton.h"
#include <QPainter>

CoinButton::CoinButton(QWidget *parent) : QPushButton(parent)
{
    // 初始状态
    this->setState(0);
    //设置按钮不规则样式，去掉边框
    this->setStyleSheet("QPushButton{border:0px;}");
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

void CoinButton::flip()
{
    this->mState = !this->mState;
    this->setState(this->mState);
}

void CoinButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QPixmap pix(":/res/BoardNode.png");

    painter.drawPixmap(0,0,this->width(), this->height(), pix);

    QPushButton::paintEvent(event);
}
