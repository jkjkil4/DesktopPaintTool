#ifndef TOOLLIST_H
#define TOOLLIST_H

#include <QWidget>

#include <QTimer>
#include <QWheelEvent>
#include <QMouseEvent>

#include "Class/toolitem.h"
#include "header.h"
#include "Widget/paintwidget.h"


/*
    ToolList
    工具列表
*/
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

    struct Item //用来将ToolItem和ProcFunc对应的结构体
    {
        Item() = default;
        Item(const ToolItem& toolItem, PaintWidget::ProcFunc procFunc)
            : toolItem(toolItem), procFunc(procFunc) {}

        ToolItem toolItem;
        PaintWidget::ProcFunc procFunc = nullptr;
    };
    QVector<Item> vItems = {
        //画笔
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
        //橡皮擦
        Item(ToolItem(QIcon(":/ToolBtn/Resource/ToolEraser.png"), "橡皮擦"),
        [](QImage &img, QPoint posBefore, QPoint pos, int size, QRect &updateRect){
            int size_ = 2 * size;
            QPainter p(&img);
            p.setCompositionMode(QPainter::CompositionMode_Clear);  //将绘制模式设置为清空
            p.setPen(QPen(Qt::black, size_ * 2));
            p.drawLine(posBefore, pos);
            int x = qMax(0, pos.x() - size_ - 2);
            int y = qMax(0, pos.y() - size_ - 2);
            int w = qMin(img.width() - x, 2 * size_ + 4);
            int h = qMin(img.height() - y, 2 * size_ + 4);
            sumRect(updateRect, QRect(x, y, w, h));
        })
    };

    SC int btnWidth = 60;
    SC int btnHeight = 60;
    SC int spacing = 5;
    SC int margin = 5;

    void setMouseIndex(int index);

signals:
    void toolChanged(); //当工具改变时发出的信号

private slots:
    void onTimerUpdateOffset();
    void onTimerCheckMouseOut();

private:
    QTimer *timerUpdate = new QTimer(this); //用来限制update频率的定时器

    QTimer *timerUpdateOffset = new QTimer(this);   //用来控制偏移更新的定时器
    int yOffset = 0;    //纵向偏移
    int spd = 0;    //偏移的速度

    void updateMouseIndexByMousePos();  //根据鼠标的位置来更新mouseIndex
    int getMouseIndex(QPoint pos);  //根据位置得到mouseIndex
    QTimer *timerCheckMouseOut = new QTimer(this);  //用来检测鼠标移出控件的定时器
    int mouseIndex = -1;
    bool isHolding = false;

    QColor color1 = QColor(210, 210, 210);  //默认颜色
    QColor color2 = QColor(230, 230, 230);  //鼠标悬停时的颜色
    QColor color3 = QColor(190, 190, 210);  //鼠标按下时的颜色
};

#endif // TOOLLIST_H
