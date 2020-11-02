#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "xyteacher.h"
#include "wtstudent.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    void xtClassIsOver();

    void test1();
    void test2();
    void test3();
    void test4();
    void test5();
    void test6();
    void test7();

private:
    XYTeacher *pTeacher;
    WtStudent *pStudent;

};

#endif // WIDGET_H
