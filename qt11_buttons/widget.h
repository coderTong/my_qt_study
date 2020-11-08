#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_radioButton_clicked();

    void on_checkBox_4_clicked();

    void on_checkBox_4_stateChanged(int arg1);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
