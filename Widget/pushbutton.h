#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QAbstractButton>

#include "header.h"


/*
    PushButton
    带有一个图标和一个文字的按钮
*/
class PushButton : public QAbstractButton
{
protected:
    void mouseMoveEvent(QMouseEvent *) override {}
    void keyPressEvent(QKeyEvent *) override {}
    void keyReleaseEvent(QKeyEvent *) override {}
    void paintEvent(QPaintEvent *) override;

public:
    PushButton(const QIcon &icon, const QString &text, QWidget *parent = nullptr);

    bool checkMouseAt();

    VAR_FUNC(Icon, icon, QIcon)
    VAR_FUNC(IconSize, iconSize, QSize)
    VAR_FUNC(Text, text, QString)
    VAR_FUNC(Color1, color1, QColor)
    VAR_FUNC(Color2, color2, QColor)
    VAR_FUNC(Color3, color3, QColor)

private:
    QIcon icon;
    QSize iconSize = QSize(16, 16);
    QString text;
    QColor color1 = QColor(240, 240, 240);  //默认颜色
    QColor color2 = QColor(180, 180, 250);  //鼠标悬停时的颜色
    QColor color3 = QColor(200, 200, 200);  //鼠标按下时的颜色
};

#endif // PUSHBUTTON_H
