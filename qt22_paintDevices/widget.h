#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QPaintEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // WIDGET_H
