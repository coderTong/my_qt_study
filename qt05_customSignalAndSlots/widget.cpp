#include "widget.h"
#include <QPushButton>

#include <QDebug>
#include "wtqpushbutton.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //    自定义信号
    //        1 函数声明在类头文件的signals 域下面
    //        2 void 类型的函数，没有返回值
    //        3 可以有参数，也可以重载
    //        4 只有声明，没有实现定义
    //        5 触发信号 emit obj->sign(参数...)

    //    自定义槽
    //        1 函数声明在类头文件的public/private/protected slots域下面（qt4以前的版本）
    //            qt5 就可以声明在类的任何位置，还可以是静态成员函数、全局函数、lambda表达式
    //        2 void 类型的函数，没有返回值
    //        3 可以有参数，也可以重载
    //        4 不仅有声明，还得有实现

    pTeacher = new XYTeacher(this);
    pStudent = new WtStudent(this);
//    connect(pTeacher, &XYTeacher::hungry, pStudent, &WtStudent::treat);


    //因为函数发生了重载，所以解决
    /*
     * 1 使用函数指针赋值，让编译器挑选符合类型的函数
     * 2 使用static_cast 强制转换，也是让编译器自动挑选符合类型的函数
     */
//    void (XYTeacher::*teacher_qString)(QString) = &XYTeacher::hungry;
//    void (WtStudent::*student_qString)(QString) = &WtStudent::treat;
//    connect(pTeacher, teacher_qString, pStudent, student_qString);


//    //使用static_cast 来转换无参的函数
//    connect(pTeacher,
//            static_cast< void (XYTeacher::*)(void) >(&XYTeacher::hungry),
//            pStudent,
//            static_cast< void (WtStudent::*)(void) >(&WtStudent::treat)  );


    //使用static_cast 来转换有参的函数
//    connect(pTeacher,
//            static_cast< void (XYTeacher::*)(QString) >(&XYTeacher::hungry),
//            pStudent,
//            static_cast< void (WtStudent::*)(QString) >(&WtStudent::treat)  );

    // 信号可以连接信号

//    QPushButton *btn = new QPushButton("按钮1", this);
//    connect(btn,
//            &QPushButton::clicked,
//            pTeacher,
//            static_cast< void (XYTeacher::*)()  >(&XYTeacher::hungry));

//    QPushButton *btn = new QPushButton("按钮1",this);
//    connect(btn,
//            &QPushButton::clicked,
//            pTeacher,
//            static_cast< void (XYTeacher::*)() >( &XYTeacher::hungry ));


//        connect(btn,&QPushButton::clicked,pTeacher,&XYTeacher::hungry);

//    connect(btn, &QPushButton::clicked, pTeacher, teacher_qString);
    // 信号可以断开连接


//    this->xtClassIsOver();

//    QPushButton *btn = new QPushButton("按钮1",this);
//    connect(btn,
//            &QPushButton::clicked,
//            pTeacher,
//            static_cast< void (XYTeacher::*)() >( &XYTeacher::hungry ));

    test7();
}

//Widget::test1()
//{
//    qDebug() << "hello";

//    //    自定义信号
//    //        1 函数声明在类头文件的signals 域下面
//    //        2 void 类型的函数，没有返回值
//    //        3 可以有参数，也可以重载
//    //        4 只有声明，没有实现定义
//    //        5 触发信号 emit obj->sign(参数...)

//    //    自定义槽
//    //        1 函数声明在类头文件的public/private/protected slots域下面（qt4以前的版本）
//    //            qt5 就可以声明在类的任何位置，还可以是静态成员函数、全局函数、lambda表达式
//    //        2 void 类型的函数，没有返回值
//    //        3 可以有参数，也可以重载
//    //        4 不仅有声明，还得有实现

//    pTeacher = new XYTeacher(this);
//    pStudent = new WtStudent(this);
//    connect(pTeacher, &XYTeacher::hungry, pStudent, &WtStudent::treat);
//}

Widget::~Widget()
{

}



void Widget::test1()
{
    //    自定义信号
    //        1 函数声明在类头文件的signals 域下面
    //        2 void 类型的函数，没有返回值
    //        3 可以有参数，也可以重载
    //        4 只有声明，没有实现定义
    //        5 触发信号 emit obj->sign(参数...)

    //    自定义槽
    //        1 函数声明在类头文件的public/private/protected slots域下面（qt4以前的版本）
    //            qt5 就可以声明在类的任何位置，还可以是静态成员函数、全局函数、lambda表达式
    //        2 void 类型的函数，没有返回值
    //        3 可以有参数，也可以重载
    //        4 不仅有声明，还得有实现

    /*
     这个是没有那啥, 没有重载函数才能这么写哈

    */


//    pTeacher = new XYTeacher(this);
//    pStudent = new WtStudent(this);
//    connect(pTeacher, &XYTeacher::hungry, pStudent, &WtStudent::treat);
    //    this->xtClassIsOver();
}

void Widget::test2()
{

    /*
     这个方法重载时的
    */
    pTeacher = new XYTeacher(this);
    pStudent = new WtStudent(this);

    void (XYTeacher::*teacher_qString)(QString) = &XYTeacher::hungry;
    void (WtStudent::*student_qString)(QString) = &WtStudent::treat;
    connect(pTeacher, teacher_qString, pStudent, student_qString);

    this->xtClassIsOver();
}

void Widget::test3()
{
    pTeacher = new XYTeacher(this);
    pStudent = new WtStudent(this);

    //使用static_cast 来转换无参的函数
    connect(pTeacher,
            static_cast< void (XYTeacher::*)(void) >(&XYTeacher::hungry),
            pStudent,
            static_cast< void (WtStudent::*)(void) >(&WtStudent::treat)  );

    this->xtClassIsOver();
}


void Widget::test4()
{
    pTeacher = new XYTeacher(this);
    pStudent = new WtStudent(this);


    //使用static_cast 来转换有参的函数
    connect(pTeacher,
            static_cast< void (XYTeacher::*)(QString) >(&XYTeacher::hungry),
            pStudent,
            static_cast< void (WtStudent::*)(QString) >(&WtStudent::treat)  );

    this->xtClassIsOver();
}

void Widget::test5()
{
    pTeacher = new XYTeacher(this);
    pStudent = new WtStudent(this);


    connect(pTeacher,
            static_cast< void (XYTeacher::*)() >(&XYTeacher::hungry),
            pStudent,
            static_cast< void (WtStudent::*)() >(&WtStudent::treat)  );

    QPushButton *btn = new QPushButton("按钮1",this);

    connect(btn,
                &QPushButton::clicked,
                pTeacher,
                static_cast< void (XYTeacher::*)() >( &XYTeacher::hungry ));


//    this->xtClassIsOver();
}

void Widget::test6()
{
    pTeacher = new XYTeacher(this);
    pStudent = new WtStudent(this);

    void (XYTeacher::*teacher_qString)() = &XYTeacher::hungry;
    void (WtStudent::*student_qString)() = &WtStudent::treat;
    connect(pTeacher, teacher_qString, pStudent, student_qString);

    QPushButton *btn = new QPushButton("按钮1",this);

    connect(btn,

            &QPushButton::clicked,
            pTeacher,
            teacher_qString );

    //信号可以断开连接
//    disconnect(pTeacher,teacher_qString,pStudent,student_qString);

    this->xtClassIsOver();
}

void Widget::test7()
{
    pTeacher = new XYTeacher(this);
    pStudent = new WtStudent(this);

    /*
     2020年11月01日22:51:31
     实际上这个是没意义的, 信号有只是函数, 不能继承, 所以只能用空参数的就ok了
    */

    connect(pTeacher,
            static_cast< void (XYTeacher::*)(QString) >(&XYTeacher::hungry),
            pStudent,
            static_cast< void (WtStudent::*)(QString) >(&WtStudent::treat)  );

    WTQPushButton *btn = new WTQPushButton("ss", this);//new WTQPushButton("按钮1",this);
    connect(btn,
            static_cast< void (WTQPushButton::*)(QString) >( &WTQPushButton::clicked),
            pTeacher,
            static_cast< void (XYTeacher::*)(QString) >(&XYTeacher::hungry) );

}

void Widget::xtClassIsOver()
{
//    emit pTeacher->hungry();
    emit pTeacher->hungry("黄焖鸡");
}
