#ifndef MYQDIALOG_H
#define MYQDIALOG_H

#include <QDialog>

#include <QCloseEvent>
class MyQDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MyQDialog(QWidget *parent = nullptr);

signals:

public slots:

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MYQDIALOG_H
