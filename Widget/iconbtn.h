#ifndef ICONBTN_H
#define ICONBTN_H

#include <QAbstractButton>

#include "header.h"

class IconBtn : public QAbstractButton
{
protected:
    void mouseMoveEvent(QMouseEvent *) override {}
    void keyPressEvent(QKeyEvent *) override {}
    void keyReleaseEvent(QKeyEvent *) override {}
    void paintEvent(QPaintEvent *) override;

public:
    explicit IconBtn(QWidget *parent = nullptr);
    explicit IconBtn(QIcon icon, QWidget *parent = nullptr);
    ~IconBtn() override = default;

    bool checkMouseAt();

//    VAR_FUNC(BgColor, bgColor, QColor)

//private:
//    QColor bgColor = QColor(102, 204, 255);
};

#endif // ICONBTN_H
