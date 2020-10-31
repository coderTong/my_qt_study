#ifndef TOMWIDGET_H
#define TOMWIDGET_H

#include <QWidget>

class TomWidget : public QWidget
{
    Q_OBJECT

public:
    TomWidget(QWidget *parent = 0);
    ~TomWidget();
};

#endif // TOMWIDGET_H
