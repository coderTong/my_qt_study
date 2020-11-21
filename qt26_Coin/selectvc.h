#ifndef SELECTVC_H
#define SELECTVC_H

#include <QMainWindow>
#include "wtmainwindow.h"

#include <QPushButton>

class SelectVC : public WTMainWindow
{
    Q_OBJECT
public:
    explicit SelectVC(QWidget *parent = nullptr);

signals:
    void wtBackBtnClicked();

public slots:
};

#endif // SELECTVC_H
