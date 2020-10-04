#ifndef TOOLITEM_H
#define TOOLITEM_H

#include <QPainter>
#include <QIcon>

#include "header.h"


/*
    ToolItem
    用来对工具的内容进行绘制
*/
class ToolItem
{
public:
    ToolItem() = default;
    ToolItem(const QIcon &icon, const QString &text);
    void onPaint(QPainter &p, QRect r);

    SC int iconWidth = 40;  //图像宽度
    SC int iconHeight = 40; //图像高度

    QIcon icon;     //图像
    QString text;   //文字

    static ToolItem *current;   //当前ToolItem
};

#endif // TOOLITEM_H
