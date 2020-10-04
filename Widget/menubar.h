#ifndef MENUBAR_H
#define MENUBAR_H

#include <QWidget>
#include <QHBoxLayout>

#include <QMouseEvent>
#include <QPainter>

#include "header.h"
#include "statebtn.h"
#include "iconbtn.h"


/*
    MenuBar
    菜单栏
*/
class MenuBar : public QWidget
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void paintEvent(QPaintEvent *) override;

public:
    explicit MenuBar(QWidget *parent = nullptr);
    ~MenuBar() override = default;

    VAR_FUNC_UPDATE(BgColor, bgColor, QColor)
    VAR_FUNC_UPDATE(DotColor, dotColor, QColor)
    VAR_FUNC_UPDATE(DotCount, dotRadius, int)
    VAR_FUNC_UPDATE(DotSpacing, dotSpacing, int)

signals:
    void wndMoveOffset(int xOffset, int yOffset);   //需要移动窗口时发出的信号
    void foldStateChanged(bool state);  //折叠按钮状态改变时发出的信号
    void wndClose();    //需要关闭窗口时发出的信号

private:
    //绘制的相关设置
    QColor bgColor = QColor(225, 225, 225);
    QColor dotColor = QColor(170, 170, 170);
    int dotRadius = 2;
    int dotSpacing = 3;
    static constexpr int dotCount = 4;

    //用于窗体的移动
    QPoint mousePosStart;
};

#endif // MENUBAR_H
