#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);



    /*
     QListWidgetItem形式
    */
//    QListWidgetItem *item = new QListWidgetItem("君不见黄河之水天上来");
//    item->setTextAlignment(Qt::AlignHCenter);
//    QListWidgetItem *item2 = new QListWidgetItem("君不见，高堂明镜悲白发，朝如青丝暮成雪。");
//    item2->setTextAlignment(Qt::AlignHCenter);
//    //
//    ui->listWidget->addItem(item);
//    ui->listWidget->addItem(item2);


    //QString 相当于 -> std::string  QList 相当于 -> std::list   QStringList 相当于 -> std::list<std::string>
    QStringList list;
    list << "君不见，黄河之水天上来，奔流到海不复回。"
         << "君不见，高堂明镜悲白发，朝如青丝暮成雪。"
         << "人生得意须尽欢，莫使金樽空对月。"
         << "天生我材必有用，千金散尽还复来。"
         << "烹羊宰牛且为乐，会须一饮三百杯。"
         << "岑夫子，丹丘生，将进酒，杯莫停。"
         << "与君歌一曲，请君为我倾耳听。"
         << "钟鼓馔玉不足贵，但愿长醉不愿醒"
         << "古来圣贤皆寂寞，惟有饮者留其名。"
         << "陈王昔时宴平乐，斗酒十千恣欢谑。"
         << "主人何为言少钱，径须沽取对君酌。"
         << "五花马，千金裘，呼儿将出换美酒，与尔同销万古愁。"
         << "========================================"
         << "君不见，黄河之水天上来，奔流到海不复回。"
         << "君不见，高堂明镜悲白发，朝如青丝暮成雪。"
         << "人生得意须尽欢，莫使金樽空对月。"
         << "天生我材必有用，千金散尽还复来。"
         << "烹羊宰牛且为乐，会须一饮三百杯。"
         << "岑夫子，丹丘生，将进酒，杯莫停。"
         << "与君歌一曲，请君为我倾耳听。"
         << "钟鼓馔玉不足贵，但愿长醉不愿醒"
         << "古来圣贤皆寂寞，惟有饮者留其名。"
         << "陈王昔时宴平乐，斗酒十千恣欢谑。"
         << "主人何为言少钱，径须沽取对君酌。"
         << "五花马，千金裘，呼儿将出换美酒，与尔同销万古愁。";
    ui->listWidget->addItems(list);

}

Widget::~Widget()
{
    delete ui;
}
