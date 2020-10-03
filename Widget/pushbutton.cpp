#include "pushbutton.h"

PushButton::PushButton(const QIcon &icon, const QString &text, QWidget *parent)
    : QAbstractButton(parent), icon(icon), text(text)
{
    limitHeight(this, 24);
}

bool PushButton::checkMouseAt() {
    QPoint mouse = mapFromGlobal(cursor().pos());
    return QRect(0, 0, width(), height()).contains(mouse);
}

void PushButton::paintEvent(QPaintEvent *) {
    QPainter p(this);

    jDrawRecFrame(p, 0, 0, width(), height(), 1, Qt::darkGray);

    p.fillRect(1, 1, width() - 2, height() - 2, isEnabled() ? (isDown() ? color3 : (checkMouseAt() ? color2 : color1)) : color1.darker(120));

    int align = (height() - iconSize.height()) / 2;
    icon.paint(&p, QRect(align, align, iconSize.width(), iconSize.height()));

    int textAlign = 2 * align + iconSize.width();
    p.drawText(QRect(textAlign, 0, width() - textAlign, height()), Qt::AlignLeft | Qt::AlignVCenter, text);
}
