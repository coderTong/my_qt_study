#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QPaintEvent>
#include <QPainter>


class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = nullptr);

    void moveDown();
    void moveUp();

signals:

protected:
    void paintEvent(QPaintEvent *event);

public slots:
};

#endif // MYBUTTON_H
