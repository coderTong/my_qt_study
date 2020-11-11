#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // treeWidget 使用

    // 1. 设置标题
    ui->treeWidget->setHeaderLabels(QStringList() << "英雄" << "简介");

    // 2. 添加根节点
//    QTreeWidgetItem *item1 = new QTreeWidgetItem(QStringList() << "力量" <<"ddd");
    QTreeWidgetItem *item1 = new QTreeWidgetItem(QStringList() << "力量");
    QTreeWidgetItem *item2 = new QTreeWidgetItem(QStringList() << "敏捷");
    QTreeWidgetItem *item3 = new QTreeWidgetItem(QStringList() << "智力");
    ui->treeWidget->addTopLevelItem(item1);
    ui->treeWidget->addTopLevelItem(item2);
    ui->treeWidget->addTopLevelItem(item3);

    // 3. 添加相应的子节点
    item1->addChild(new QTreeWidgetItem(QStringList() << "阿古朵" << "球球抱住阿古朵翻滚蓄力，持续对周围造成物理伤害。蓄力完成后冲锋而出，对触碰的敌人造成物理伤害，冲锋距离随蓄力时间而增加，整个施法期间可免疫1次硬控效果，取消施法执行70%冷却时间。 被动：收服蜥蜴的数量超过2/4/6时，会在冲锋首次命中敌人处或终点处召唤小/中/大红隼前来助战"));
    item2->addChild(new QTreeWidgetItem(QStringList() << "孙悟空" << "孙悟空将变大的金箍棒直插入地，对范围内敌人造成150/190/230（+50%物理加成）点物理伤害并将其晕眩1秒。同时范围内敌人获得3层印记；孙悟空的普通攻击命中带有印记的敌人将消耗1层印记并额外造成270/405/540点物理伤害。"));
    item3->addChild(new QTreeWidgetItem(QStringList() << "亚瑟" << "亚瑟举起圣剑跃向敌方英雄，造成敌方英雄最大生命12/16/20%法术伤害并将其击飞0.5秒；同时召唤圣印覆盖落点范围，持续5秒，圣印会对范围内敌人造成每秒85/105/125点法术伤害"));
}

Widget::~Widget()
{
    delete ui;
}
