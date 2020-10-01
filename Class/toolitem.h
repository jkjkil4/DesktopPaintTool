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
    void onPaint(QPainter &p, QPoint pos);

    int width = 70;      //区域宽度
    int height = 70;     //区域高度
    SC int iconWidth = 40;  //图像宽度
    SC int iconHeight = 40; //图像高度

    QIcon icon;     //图像
    QString text;   //文字

    static ToolItem *current;
};

#endif // TOOLITEM_H
