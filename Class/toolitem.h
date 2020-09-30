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
    void onPaint(QPainter &p, QPoint pos) {
        QRegion prevRegion = p.clipRegion();    //得到原先的clipRegion
        p.setClipRect(pos.x(), pos.y(), width, height); //设置clipRegion

        SC int spacing = 2;     //图像与文字之间的空隙
        int tmHeight = QFontMetrics(p.font()).height();     //文字的高度
        int totalHeight = iconHeight + spacing + tmHeight;      //总高度(图像高度 + 空隙 + 文字高度)
        SC int xPos = (width - iconWidth) / 2;    //绘制的x坐标(图像的左上角)
        int yPos = (height - totalHeight) / 2;    //绘制的y坐标(图像的左上角)
        icon.paint(&p, QRect(pos.x() + xPos, pos.y() + yPos, iconWidth, iconHeight));   //绘制图像
        p.drawText(QRect(pos.x(), pos.y() + yPos + iconHeight + spacing, width, tmHeight),
                   Qt::AlignTop | Qt::AlignCenter, text);   //绘制文字

        p.setClipRegion(prevRegion);    //还原clipRegion
    }
    SC int width = 70;      //区域宽度
    SC int height = 70;     //区域高度
    SC int iconWidth = 40;  //图像宽度
    SC int iconHeight = 40; //图像高度

    QIcon icon;     //图像
    QString text;   //文字
};

#endif // TOOLITEM_H
