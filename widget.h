#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>

#include <QGuiApplication>
#include <QScreen>

#include "header.h"
#include "Widget/menubar.h"

class Widget : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *) override;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget() override;

private:
    QWidget *toolsWidget = new QWidget;
};

#endif // WIDGET_H
