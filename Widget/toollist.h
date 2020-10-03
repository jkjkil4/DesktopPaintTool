#ifndef TOOLLIST_H
#define TOOLLIST_H

#include <QWidget>

#include <QTimer>
#include <QWheelEvent>
#include <QMouseEvent>

#include "Class/toolitem.h"
#include "header.h"
#include "Widget/paintwidget.h"

class ToolList : public QWidget
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void wheelEvent(QWheelEvent *ev) override;
    void paintEvent(QPaintEvent *) override;

public:
    explicit ToolList(QWidget *parent = nullptr);
    ~ToolList() override = default;

    struct Item
    {
        Item() = default;
        Item(const ToolItem& toolItem, PaintWidget::ProcFunc procFunc)
            : toolItem(toolItem), procFunc(procFunc) {}

        ToolItem toolItem;
        PaintWidget::ProcFunc procFunc = nullptr;
    };
    QVector<Item> vItems = {
        Item(ToolItem(QIcon(":/ToolBtn/Resource/ToolBrush.png"), "画笔"),
        [](QImage &img, QPoint posBefore, QPoint pos, int size, QRect &updateRect){
            QPainter p(&img);
            p.setPen(QPen(Qt::red, size));
            p.drawLine(posBefore, pos);
            int x = qMax(0, pos.x() - size - 2);
            int y = qMax(0, pos.y() - size - 2);
            int w = qMin(img.width() - x, 2 * size + 4);
            int h = qMin(img.height() - y, 2 * size + 4);
            sumRect(updateRect, QRect(x, y, w, h));
        }),
        Item(ToolItem(QIcon(":/ToolBtn/Resource/ToolEraser.png"), "橡皮擦"),
        [](QImage &img, QPoint, QPoint pos, int size, QRect &updateRect){
            QPainter p(&img);
            int size_ = size * 2;
            int xStart = qMax(0, pos.x() - size_);
            int xEnd = qMin(img.width(), pos.x() + size_);
            int yStart = qMax(0, pos.y() - size_);
            int yEnd = qMin(img.height(), pos.y() + size_);
            for(int j = yStart; j < yEnd; j++) {
                for(int i = xStart; i < xEnd; i++) {
                    img.setPixel(i, j, qRgba(0, 0, 0, 0));
                }
            }
            sumRect(updateRect, QRect(xStart, yStart, xEnd - xStart, yEnd - yStart));
        })
    };

    SC int btnWidth = 60;
    SC int btnHeight = 60;
    SC int spacing = 5;
    SC int margin = 5;

    void setMouseIndex(int index);

signals:
    void toolChanged();

private slots:
    void onTimerUpdateOffset();
    void onTimerCheckMouseOut();

private:
    QTimer *timerUpdate = new QTimer(this);

    QTimer *timerUpdateOffset = new QTimer(this);
    int yOffset = 0;
    int spd = 0;

    void updateMouseIndexByMousePos();
    int getMouseIndex(QPoint pos);
    QTimer *timerCheckMouseOut = new QTimer(this);
    int mouseIndex = -1;
    bool isHolding = false;

    QColor color1 = QColor(210, 210, 210);
    QColor color2 = QColor(230, 230, 230);
    QColor color3 = QColor(190, 190, 210);
};

#endif // TOOLLIST_H
