#include "myview.h"
#include "ui_myview.h"

MyView::MyView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyView)
{
    ui->setupUi(this);

    // 设置数字范围
    ui->horizontalSlider->setRange(0, 100);
    ui->spinBox->setRange(0,100);

    // 建立两个控件的关联
    connect(ui->horizontalSlider, &QSlider::valueChanged, [=](int value){

        ui->spinBox->setValue(value);
    });


    // 调整计数器的时候, 滚桥也跟着变化
    // 这里有重载函数二义性, 所以需要强制转换
    connect(ui->spinBox, static_cast< void (QSpinBox::*)(int) >(&QSpinBox::valueChanged), ui->horizontalSlider, &QSlider::setValue);

}

MyView::~MyView()
{
    delete ui;
}

void MyView::setMyValue(int value)
{
    ui->horizontalSlider->setValue(value);
}

int MyView::valueMy() const
{
    return ui->horizontalSlider->value();
}
