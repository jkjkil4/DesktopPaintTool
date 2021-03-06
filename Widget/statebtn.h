#ifndef STATEBTN_H
#define STATEBTN_H

#include <QAbstractButton>

#include <QPainter>

#include "header.h"


/*
    StateBtn
    在被点击后会在两个图标间切换，并且发出stateChanged信号
*/
class StateBtn : public QAbstractButton
{
    Q_OBJECT
protected:
    void mouseMoveEvent(QMouseEvent *) override {}
    void keyPressEvent(QKeyEvent *) override {}
    void keyReleaseEvent(QKeyEvent *) override {}
    void paintEvent(QPaintEvent *) override;

public:
    StateBtn(const QIcon &icon1, const QIcon &icon2);
    ~StateBtn() override = default;

    VAR_FUNC_UPDATE(Icon1, icon1, QIcon)
    VAR_FUNC_UPDATE(Icon2, icon2, QIcon)
    VAR_FUNC_UPDATE(State, state, bool)

signals:
    void stateChanged(bool state);

private:
    QIcon icon1;
    QIcon icon2;

    bool state = false;
};

#endif // STATEBTN_H
