#include "paintwidget.h"

PaintWidget* PaintWidget::ins = nullptr;

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    imgBefore.fill(QColor(0, 0, 0, 0));
    imgNow.fill(QColor(0, 0, 0, 0));

    QRect desktopRect = QGuiApplication::primaryScreen()->geometry();
    setGeometry(0, 0, desktopRect.width(), desktopRect.height());

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SubWindow);
    setAttribute(Qt::WA_TranslucentBackground);
}

void PaintWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), QColor(0, 0, 0, 1));

}
