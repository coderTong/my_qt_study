#ifndef PLAYVC_H
#define PLAYVC_H

#include <QMainWindow>
#include "wtmainwindow.h"
#include "coinbutton.h"
class PlayVC : public WTMainWindow
{
    Q_OBJECT
public:
    PlayVC(int level, QWidget *parent = nullptr);
    ~PlayVC();

    // 翻动 row行 col列硬币
    void flip(int row, int col);

signals:
    void wtBackBtnClicked();

public slots:

protected:
    void paintEvent(QPaintEvent *event);

private:

    void judgeWin();

    // 硬币数组
    CoinButton *mCoins[4][4];

    //
    bool mHasWin;
};

#endif // PLAYVC_H
