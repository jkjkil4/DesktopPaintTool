#include "toollist.h"

ToolList::ToolList(QWidget *parent) : QWidget(parent)
{
    timerUpdate->setSingleShot(true);
    connect(timerUpdate, SIGNAL(timeout()), this, SLOT(update()));
    connect(timerUpdateOffset, SIGNAL(timeout()), this, SLOT(onTimerUpdateOffset()));
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


int ToolList::getMouseIndex(int y) {
    int yPos = y - yOffset - margin;
    if(yPos < 0) return -1;

    int yLocal = yPos % (btnHeight + spacing);
    if(yLocal > btnHeight) return -1;

    int yIndex = yPos / (btnHeight + spacing);
    return yIndex;
}

void ToolList::updateMouseIndexByMousePos() {
    QPoint mousePos = mapFromGlobal(cursor().pos());
    mouseIndex = getMouseIndex(mousePos.y());
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

    p.fillRect(0, 10 + yOffset, 40, 40, Qt::green);

    jDrawRecFrame(p, 0, 0, width(), height(), 1, QColor(210, 210, 210));
}
