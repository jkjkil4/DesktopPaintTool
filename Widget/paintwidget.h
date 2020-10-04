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


/*
    PaintWidget
    用来绘制的"画板"
*/
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

    static PaintWidget *ins;    //便于直接通过PaintWidget::ins来调用

    ProcFunc procFunc = nullptr;    //图像处理的函数指针

signals:
    void painted(); //当内容发生改变时发出的信号

private:
    QTimer *timerUpdate = new QTimer(this); //用来限制update频率的定时器
    QPoint posBefore;   //上一个绘制的位置
    QImage imgBefore, imgNow;   //imgNow为直接绘制到的图像，两个图像用来比较差异
    QRect updateRect;   //需要更新的区域

    //用来处理撤销和重做的东西
    //ur 是 UndoRedo 的意思
    QImage urImgBefore;
    QImage urImgNow;
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
