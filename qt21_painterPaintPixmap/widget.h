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

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;

    int mPox;
};

#endif // WIDGET_H
