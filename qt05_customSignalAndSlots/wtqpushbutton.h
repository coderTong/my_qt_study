#ifndef WTQPUSHBUTTON_H
#define WTQPUSHBUTTON_H

#include <QPushButton>

class WTQPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit WTQPushButton(QWidget *parent = nullptr);
    explicit WTQPushButton(const QString &text, QWidget *parent = Q_NULLPTR);
    //explicit WTQPushButton(QWidget *parent = nullptr);

signals:
    void clicked(QString);

public slots:
};

#endif // WTQPUSHBUTTON_H
