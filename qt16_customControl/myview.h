#ifndef MYVIEW_H
#define MYVIEW_H

#include <QWidget>

namespace Ui {
class MyView;
}

class MyView : public QWidget
{
    Q_OBJECT

public:
    explicit MyView(QWidget *parent = nullptr);
    ~MyView();

    // 提供结构给他们访问

    void setMyValue(int value);


    int valueMy()const;

private:
    Ui::MyView *ui;
};

#endif // MYVIEW_H
