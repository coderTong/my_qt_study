#ifndef XYTEACHER_H
#define XYTEACHER_H

#include <QObject>

class XYTeacher : public QObject
{
    Q_OBJECT
public:
    explicit XYTeacher(QObject *parent = nullptr);

signals:
    //    自定义信号
        //        1 函数声明在类头文件的signals 域下面
        //        2 void 类型的函数，没有返回值
        //        3 可以有参数，也可以重载
        //        4 只有声明，没有实现定义
        //        5 触发信号 emit obj->sign(参数...)
    void hungry();
    void hungry(QString foot);

public slots:
};

#endif // XYTEACHER_H
