#ifndef WTPUSHBUTTON_H
#define WTPUSHBUTTON_H

#include <QPushButton>

class WTPushButton : public QPushButton
{
    Q_OBJECT
public:

    enum WTPushButtonStat
    {
        Normal,
        Entered,
        Pressed
    };

    explicit WTPushButton(QWidget *parent = nullptr);



signals:

public slots:

protected:
    void paintEvent(QPaintEvent *e);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    WTPushButtonStat mStat;
};

#endif // WTPUSHBUTTON_H
