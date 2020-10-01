#include "toollist.h"

ToolList::ToolList(QWidget *parent) : QWidget(parent)
{
    timerUpdate->setSingleShot(true);
    connect(timerUpdate, SIGNAL(timeout()), this, SLOT(update()));
    connect(timerUpdateOffset, SIGNAL(timeout()), this, SLOT(onTimerUpdateOffset()));
    connect(timerCheckMouseOut, SIGNAL(timeout()), this, SLOT(onTimerCheckMouseOut()));

    setMouseTracking(true);
}


void ToolList::setMouseIndex(int index) {
    if(index != mouseIndex) {
        mouseIndex = index;
        START_TIMER(timerUpdate, 16);
    }
}

void ToolList::onTimerUpdateOffset() {
    if (spd != 0) {
        //sumSpdToOffset
        yOffset += spd;
        if (spd > 0) {
            spd -= 1;
            if (spd < 0)
                spd = 0;
        }
        else if (spd < 0) {
            spd += 1;
            if (spd > 0)
                spd = 0;
        }
    }

    bool isMoving = false;
    int min = qMin<int>(height() - ((btnHeight + spacing) * vItems.size() + 2 * margin - spacing), 0);
    if (yOffset > 0 || yOffset < min) {
        //isMoving = limitOffset(min);
        //limitOffset
        if (yOffset > 0) {
            int limitSpd = 2 + yOffset / 4;
            yOffset -= limitSpd;
            if (yOffset < 0)
                yOffset = 0;
            isMoving = true;
        } else if (yOffset < min) {
            int limitSpd = 2 + (min - yOffset) / 4;
            yOffset += limitSpd;
            if (yOffset > min)
                yOffset = min;
            isMoving = true;
        } else isMoving = false;
    }

    updateMouseIndexByMousePos();

    START_TIMER(timerUpdate, 16);

    if(spd == 0 && !isMoving)
        timerUpdateOffset->stop();
}


int ToolList::getMouseIndex(QPoint pos) {
    if(pos.x() < (width() - btnWidth) / 2 || pos.x() > (width() + btnWidth) / 2)
        return -1;

    int yPos = pos.y() - yOffset - margin;
    if(yPos < 0) return -1;

    int yLocal = yPos % (btnHeight + spacing);
    if(yLocal > btnHeight) return -1;

    int yIndex = yPos / (btnHeight + spacing);
    if(yIndex >= vItems.size()) return -1;

    return yIndex;
}

void ToolList::updateMouseIndexByMousePos() {
    setMouseIndex(getMouseIndex(mapFromGlobal(cursor().pos())));
}

void ToolList::onTimerCheckMouseOut() {
    if(isHolding)
        return;

    if(!QRect(0, 0, width(), height()).contains(mapFromGlobal(cursor().pos()))) {
        setMouseIndex(-1);
        timerCheckMouseOut->stop();

        START_TIMER(timerUpdate, 16);
    }
}


void ToolList::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        isHolding = true;
        updateMouseIndexByMousePos();

        START_TIMER(timerUpdate, 16);
    }
}

void ToolList::mouseMoveEvent(QMouseEvent *ev) {
    if(!(ev->buttons() & Qt::LeftButton)) {
        START_TIMER(timerCheckMouseOut, 8);
        updateMouseIndexByMousePos();
    }

    START_TIMER(timerUpdate, 16);
}

void ToolList::mouseReleaseEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        if(mouseIndex != -1) {
            if(getMouseIndex(mapFromGlobal(cursor().pos())) == mouseIndex) {
                ToolItem::current = &vItems[mouseIndex].toolItem;
                PaintWidget::ins->procFunc = vItems[mouseIndex].procFunc;
                emit toolChanged();
            }
        }
        isHolding = false;
        updateMouseIndexByMousePos();
        START_TIMER(timerUpdate, 16);
    }
}

void ToolList::wheelEvent(QWheelEvent *ev) {
    int num = ev->delta() / 10;
    if ((spd < 0 && num > 0) || (spd > 0 && num < 0))
            spd = 0;
    spd += num;
    if (abs(spd) > 16)
        spd > 0 ? spd = 16 : spd = -16;

    START_TIMER(timerUpdateOffset, 16);
    START_TIMER(timerUpdate, 16);
}

void ToolList::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setClipRegion(QRect(0, 0, width(), height()));

    int startIndex = qMax(0, (-yOffset - margin) / (btnHeight + spacing));
    int endIndex = qMin(vItems.size(), (-yOffset - margin + height()) / (btnHeight + spacing) + 1);
    int xPos = (width() - btnWidth) / 2;
    for(int i = startIndex; i < endIndex; i++) {
        int yPos = margin + i * (btnHeight + spacing) + yOffset;
        ToolItem &item = vItems[i].toolItem;
        p.fillRect(xPos, yPos, btnWidth, btnHeight, ToolItem::current == &item ? color3 : (i == mouseIndex ? color2 : color1));
        item.onPaint(p, QRect(xPos, yPos, btnWidth, btnHeight));
    }

    jDrawRecFrame(p, 0, 0, width(), height(), 1, QColor(210, 210, 210));
}
