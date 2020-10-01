#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>

#include <QGuiApplication>
#include <QScreen>

class PaintWidget : public QWidget
{
protected:
    void mousePressEvent(QMouseEvent *) override;

public:
    PaintWidget(QWidget *parent = nullptr);
    ~PaintWidget() override = default;
};

#endif // PAINTWIDGET_H
