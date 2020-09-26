#include "iconbtn.h"

#include <QPainter>
#include <QDebug>

IconBtn::IconBtn(QWidget *parent)
    : QAbstractButton(parent)
{
    limitSize(this, 16, 16);
}

IconBtn::IconBtn(QIcon icon, QWidget *parent)
    : QAbstractButton(parent)
{
    limitSize(this, 16, 16);
    setIcon(icon);
}

bool IconBtn::checkMouseAt() {
    QPoint mouse = mapFromGlobal(cursor().pos());
    return QRect(0, 0, width(), height()).contains(mouse);
}


void IconBtn::paintEvent(QPaintEvent *) {
    bool mouseAt = checkMouseAt();
    bool down = isDown();

    QPainter p(this);

    if(down) {
        p.fillRect(0, 0, width(), height(), QColor(0, 0, 0, 50));
    }
    else if(mouseAt) {
        p.fillRect(0, 0, width(), height(), QColor(255, 255, 255, 50));
    }

    QSize size = iconSize();
    p.drawPixmap((width() - size.width()) / 2, (height() - size.height()) / 2, icon().pixmap(size));
}
