#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QPaintEvent>
#include <QPainter>

#include <QMouseEvent>

class MyButton : public QPushButton
{
    Q_OBJECT
public:

    enum MyButtonState
    {
        Normal,
        Pressed
    };

    MyButton(QString normalImage, QString pressedImage, QWidget *parent = nullptr);

    void moveDown();
    void moveUp();

signals:

protected:
    void paintEvent(QPaintEvent *event);

    // 鼠标按下
    void mousePressEvent(QMouseEvent *event);
    // 鼠标松开
    void mouseReleaseEvent(QMouseEvent *event);

public slots:

private:

    // 正常图片和鼠标按下的图片
    QString mNormalImage;
    QString mPressedImage;

    // 按钮状态
    MyButtonState mState;
};

#endif // MYBUTTON_H
