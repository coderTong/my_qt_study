#ifndef COINBUTTON_H
#define COINBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QPaintEvent>

#include <QTimer>

class CoinButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CoinButton(QWidget *parent = nullptr);

    int state() const;
    void setState(int state);

    void setStateWithAnimation(int state);

    void flip();

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:

private:

    // 硬币的状态, 0表示银币, 1表示金币
    // 放在上面 mac的话是option + 回车 就会有一个getter和setter方法
    int mState;
    // 记录当前帧
    int mFrame;

    // 定时器
    QTimer mTimer;

};

#endif // COINBUTTON_H
