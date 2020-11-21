#include "startvc.h"

#include <QTimer>

StartVC::StartVC(QWidget *parent) : WTMainWindow(parent)
{



    this->setWindowTitle("开始");


    MyButton * btnStart = new MyButton(":/res/MenuSceneStartButton.png",":/res/MenuSceneStartButton.png",this);
    btnStart->resize(114,114);


    int btnX = (this->width() - btnStart->width() ) / 2;
    int btnY = (this->height()*3/4 - btnStart->height() / 2);

    btnStart->move(btnX, btnY);

//    connect(this->selectVC, &SelectVC::backBtnClicked, [=](){

//    });

    connect(&this->mSelectVC, &SelectVC::wtBackBtnClicked, [=](){

        this->show();
        this->mSelectVC.hide();
    });

    connect(btnStart, &MyButton::clicked, [=](){

        // 动画完成前,按钮不可用
        btnStart->setEnabled(false);

        btnStart->moveDown();


        // 要等上面的往下的动画完成后再调用向下
        QTimer::singleShot(150, [=](){

            btnStart->moveUp();

        });


        // 动画执行完成后再将按钮可用
        QTimer::singleShot(300, [=](){

            btnStart->setEnabled(true);

            // 点击完成然后场景转换
            // 1. 隐藏当前窗口
            this->hide();
            // 2. 显示第二个窗口
            this->mSelectVC.show();
        });


        //

    });

}