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
    void on_myBtn_clicked();


public:
    void readFileTxtAll();
    void readFileTxtSingleline();
    // 指定编码
    void readFileTxtAllAndCodec();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
