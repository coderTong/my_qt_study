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
    void on_pushButton_35_clicked();

    void on_pushButton_36_clicked();

    void on_comboBox_activated(int index);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
