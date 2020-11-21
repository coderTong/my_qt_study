#ifndef MYLABEL_H
#define MYLABEL_H

#include <QWidget>
#include <QLabel>
class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr);

signals:

public slots:


protected:

    // 重写鼠标按键处理函数
    void mousePressEvent(QMouseEvent *ev);
    // 鼠标移动
    void  mouseMoveEvent(QMouseEvent *event);

    // //重写event分发函数
    bool event(QEvent *event);

    // 重写eventFilter

    bool eventFilter(QObject *watched, QEvent *event);


};

#endif // MYLABEL_H
