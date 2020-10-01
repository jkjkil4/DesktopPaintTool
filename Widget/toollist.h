#ifndef TOOLLIST_H
#define TOOLLIST_H

#include <QWidget>

#include <QTimer>
#include <QWheelEvent>

#include "Class/toolitem.h"
#include "header.h"

class ToolList : public QWidget
{
    Q_OBJECT
protected:
    void wheelEvent(QWheelEvent *ev) override;
    void paintEvent(QPaintEvent *) override;

public:
    explicit ToolList(QWidget *parent = nullptr);

    struct Item
    {
        typedef void(*Func)(QImage &tmpImg, QPoint pos, QRect &updateRect);
        ToolItem toolItem;
        Func imgProcFunc = nullptr;
    };
    QVector<Item> vItems;

    SC int btnWidth = 65;
    SC int btnHeight = 65;
    SC int spacing = 1;
    SC int margin = 1;

    void setMouseIndex();

private slots:
    void onTimerUpdateOffset();

private:
    QTimer *timerUpdate = new QTimer(this);

    QTimer *timerUpdateOffset = new QTimer(this);
    int yOffset = 0;
    int spd = 0;

    void updateMouseIndexByMousePos();
    int getMouseIndex(int y);
    int mouseIndex = -1;
};

#endif // TOOLLIST_H
