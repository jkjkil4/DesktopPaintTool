#ifndef TOOLCURSOR_H
#define TOOLCURSOR_H

#include <QAbstractButton>

#include "Class/toolitem.h"
#include "Widget/paintwidget.h"

/*
    ToolCursor
    工具栏的"鼠标"
*/
class ToolCursor : public QAbstractButton
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *) override;

public:
    explicit ToolCursor(QWidget *parent = nullptr);
    ~ToolCursor() override = default;

    bool checkMouseAt();

private:
    ToolItem toolItem;

    QColor color1 = QColor(210, 210, 210);  //默认颜色
    QColor color2 = QColor(230, 230, 230);  //鼠标悬停时的颜色
    QColor color3 = QColor(190, 190, 210);  //鼠标按下时的颜色
};

#endif // TOOLCURSOR_H
