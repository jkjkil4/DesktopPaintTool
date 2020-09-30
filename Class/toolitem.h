#ifndef TOOLITEM_H
#define TOOLITEM_H

#include <QPainter>
#include <QIcon>

#include "header.h"

class ToolItem
{
public:
    void onPaint(QPainter &p, QPoint pos) {
        QRegion prevRegion = p.clipRegion();

        p.setClipRect(pos.x(), pos.y(), width, height);

        SC int spacing = 2;
        int tmHeight = QFontMetrics(p.font()).height();
        int totalHeight = iconHeight + spacing + tmHeight;
        SC int xPos = (width - iconWidth) / 2;
        int yPos = (height - totalHeight) / 2;
        icon.paint(&p, QRect(pos.x() + xPos, pos.y() + yPos, iconWidth, iconHeight));
        p.drawText(QRect(pos.x(), pos.y() + yPos + iconHeight + spacing, width, tmHeight),
                   Qt::AlignTop | Qt::AlignCenter, text);

        p.setClipRegion(prevRegion);
    }
    SC int width = 70;
    SC int height = 70;
    SC int iconWidth = 40;
    SC int iconHeight = 40;

    QIcon icon;
    QString text;
};

#endif // TOOLITEM_H
