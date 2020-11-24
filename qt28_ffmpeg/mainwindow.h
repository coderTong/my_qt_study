#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QMutex>
#include <QDebug>
#include <QPainter>

#include "cameraclient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void onRecvFrame(char *data, int width, int height);

private:

    QMutex m_mutex;

    QImage m_image;

    Ui::MainWindow *ui;


    CameraClient*       m_camClient;

private:

    void paintEvent(QPaintEvent *);

    void PaintImage(QPainter &painter);

    void static updateVideo2GUI(RGBData_Define* rgbData,unsigned long userData);



};

#endif // MAINWINDOW_H
