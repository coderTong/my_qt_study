#ifndef PLAYVC_H
#define PLAYVC_H

#include <QMainWindow>
#include "wtmainwindow.h"
class PlayVC : public WTMainWindow
{
    Q_OBJECT
public:
    PlayVC(int level, QWidget *parent = nullptr);
    ~PlayVC();

signals:
    void wtBackBtnClicked();

public slots:

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // PLAYVC_H
