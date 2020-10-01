#ifndef TOOLLIST_H
#define TOOLLIST_H

#include <QWidget>

#include <QTimer>
#include <QWheelEvent>
#include <QMouseEvent>

#include "Class/toolitem.h"
#include "header.h"

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
        typedef void(*Func)(QImage &img, QPoint pos, QRect &updateRect);

        Item() = default;
        Item(const ToolItem& toolItem, Func imgProcFunc) : toolItem(toolItem), imgProcFunc(imgProcFunc) {}

        ToolItem toolItem;
        Func imgProcFunc = nullptr;
    };
    QVector<Item> vItems = {
        Item(ToolItem(QIcon(":/ToolBtn/Resource/ToolBrush.png"), "画笔"), nullptr),
        Item(ToolItem(QIcon(":/ToolBtn/Resource/ToolEraser.png"), "橡皮擦"), nullptr)
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
