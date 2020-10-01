#include "toolcursor.h"

ToolCursor::ToolCursor(QWidget *parent) : QAbstractButton(parent)
{
    toolItem.icon = QIcon(":/ToolBtn/Resource/ToolCursor.png");
    toolItem.text = "鼠标";
    ToolItem::current = &toolItem;

    limitSize(this, ToolItem::width, ToolItem::height);

    connect(this, &ToolCursor::clicked, [=]{ ToolItem::current = &toolItem; update(); });
}

bool ToolCursor::checkMouseAt() {
    QPoint mouse = mapFromGlobal(cursor().pos());
    return QRect(0, 0, width(), height()).contains(mouse);
}

void ToolCursor::paintEvent(QPaintEvent *) {
    QPainter p(this);

    bool mouseAt = checkMouseAt();
    bool down = isDown();
    p.fillRect(0, 0, width(), height(), (down || ToolItem::current == &toolItem) ? color3 : (mouseAt ? color2 : color1));

    toolItem.onPaint(p, QPoint(0, 0));
}
