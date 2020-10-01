#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QVBoxLayout>

#include <QGuiApplication>
#include <QScreen>
#include <QCloseEvent>

#include "header.h"
#include "Widget/menubar.h"
#include "Widget/toolcursor.h"
#include "Widget/toollist.h"
#include "Widget/paintwidget.h"


/*
    Widget
    主窗口
*/
class Widget : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *) override;
    void closeEvent(QCloseEvent *ev) override;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget() override;

private:
    QWidget *toolsWidget = new QWidget;

    ToolCursor *toolCursor = new ToolCursor;

    PaintWidget *paintWidget = new PaintWidget;
};

#endif // WIDGET_H
