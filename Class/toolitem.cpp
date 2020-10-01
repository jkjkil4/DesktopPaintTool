#include "toolitem.h"

ToolItem* ToolItem::current = nullptr;

ToolItem::ToolItem(const QIcon &icon, const QString &text)
    : icon(icon), text(text) {}

void ToolItem::onPaint(QPainter &p, QRect r) {
    QRegion prevRegion = p.clipRegion();    //得到原先的clipRegion
    p.setClipRegion(r); //设置clipRegion

    SC int spacing = 2;     //图像与文字之间的空隙
    int tmHeight = QFontMetrics(p.font()).height();     //文字的高度
    int totalHeight = iconHeight + spacing + tmHeight;      //总高度(图像高度 + 空隙 + 文字高度)
    int xPos = (r.width() - iconWidth) / 2;    //绘制的x坐标(图像的左上角)
    int yPos = (r.height() - totalHeight) / 2;    //绘制的y坐标(图像的左上角)
    icon.paint(&p, QRect(r.x() + xPos, r.y() + yPos, iconWidth, iconHeight));   //绘制图像
    p.drawText(QRect(r.x(), r.y() + yPos + iconHeight + spacing, r.width(), tmHeight),
               Qt::AlignTop | Qt::AlignCenter, text);   //绘制文字

    p.setClipRegion(prevRegion);    //还原clipRegion
}
