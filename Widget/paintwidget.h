#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>

#include <QGuiApplication>
#include <QScreen>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QDataStream>
#include <QDir>

#include "header.h"

//#define DEBUG_PAINTWIDGET

class PaintWidget : public QWidget
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void paintEvent(QPaintEvent *) override;
    void closeEvent(QCloseEvent *) override;

public:
    typedef void(*ProcFunc)(QImage &img, QPoint posBefore, QPoint pos, int size, QRect &updateRect);

    PaintWidget(QWidget *parent = nullptr);
    ~PaintWidget() override = default;

    static PaintWidget *ins;

    ProcFunc procFunc = nullptr;

signals:
    void painted();

private:
    QTimer *timerUpdate = new QTimer(this);
    QPoint posBefore;
    QImage imgBefore, imgNow;
    QRect updateRect;

    //ur means UndoRedo
    QImage urImgBefore;
    QImage urImgNow;
    //void drawImageToImage(QImage &targetImg, const QImage &img, QPoint pos);
    void urToFile(QPoint pos);
public:
    void undo();
    void redo();
    void clear();
    void btnEnabled(QWidget *widgetUndo, QWidget *widgetRedo);
private:
    uint urIndex = 0;
    uint urIndexMin = 0;
    uint urIndexMax = 0;

};

#endif // PAINTWIDGET_H
