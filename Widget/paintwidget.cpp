#include "paintwidget.h"

PaintWidget* PaintWidget::ins = nullptr;

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    QRect desktopRect = QGuiApplication::primaryScreen()->geometry();
    setGeometry(0, 0, desktopRect.width(), desktopRect.height());

    imgBefore = QImage(desktopRect.size(), QImage::Format_ARGB32);
    imgNow = QImage(desktopRect.size(), QImage::Format_ARGB32);
    imgBefore.fill(QColor(0, 0, 0, 0));
    imgNow.fill(QColor(0, 0, 0, 0));

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SubWindow);
    setAttribute(Qt::WA_TranslucentBackground);

    connect(timerUpdate, SIGNAL(timeout()), this, SLOT(update()));
}

void PaintWidget::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        if(procFunc) {
            (*procFunc)(imgNow, ev->pos(), 4, updateRect);
            START_TIMER(timerUpdate, 16);
        }
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *ev) {
    if(ev->buttons() & Qt::LeftButton) {
        if(procFunc) {
            (*procFunc)(imgNow, ev->pos(), 4, updateRect);
            START_TIMER(timerUpdate, 16);
        }
    }
}

void PaintWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), QColor(0, 0, 0, 1));

    p.drawImage(0, 0, imgNow);
}
