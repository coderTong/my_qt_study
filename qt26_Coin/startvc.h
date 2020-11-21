#ifndef STARTVC_H
#define STARTVC_H

#include "wtmainwindow.h"
#include "mybutton.h"
#include "selectvc.h"

class StartVC : public WTMainWindow
{
    Q_OBJECT
public:
    explicit StartVC(QWidget *parent = nullptr);

signals:

public slots:

private:
    SelectVC mSelectVC;
};

#endif // STARTVC_H
