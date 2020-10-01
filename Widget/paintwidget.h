#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>

#include <QGuiApplication>
#include <QScreen>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>

#include "header.h"

class PaintWidget : public QWidget
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void paintEvent(QPaintEvent *) override;

public:
    typedef void(*ProcFunc)(QImage &img, QPoint pos, int size, QRect &updateRect);

    PaintWidget(QWidget *parent = nullptr);
    ~PaintWidget() override = default;

    static PaintWidget *ins;

    ProcFunc procFunc = nullptr;

private:
    QTimer *timerUpdate = new QTimer(this);
    QImage imgBefore, imgNow;
    QRect updateRect;
};

#endif // PAINTWIDGET_H
