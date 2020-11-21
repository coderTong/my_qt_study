#ifndef WTMAINWINDOW_H
#define WTMAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>

namespace Ui {
class WTMainWindow;
}

class WTMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WTMainWindow(QWidget *parent = nullptr);
    ~WTMainWindow();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::WTMainWindow *ui;
};

#endif // WTMAINWINDOW_H
