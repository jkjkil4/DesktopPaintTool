#ifndef TOOLCURSOR_H
#define TOOLCURSOR_H

#include <QAbstractButton>

#include "Class/toolitem.h"

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

    QColor color1 = QColor(210, 210, 210);
    QColor color2 = QColor(230, 230, 230);
    QColor color3 = QColor(190, 190, 210);
};

#endif // TOOLCURSOR_H
