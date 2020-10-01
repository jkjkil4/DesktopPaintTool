#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    QRect desktopRect = QGuiApplication::primaryScreen()->availableVirtualGeometry();
    setGeometry(0, 0, desktopRect.width() / 2, desktopRect.height() / 2);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}

void PaintWidget::mousePressEvent(QMouseEvent *) {
    //lower();
}
