#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QVBoxLayout>

#include <QGuiApplication>
#include <QScreen>

#include "header.h"
#include "Widget/menubar.h"
#include "Widget/toolcursor.h"
#include "Widget/toollist.h"


/*
    Widget
    主窗口
*/
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

    ToolCursor *toolCursor = new ToolCursor;

    //TODO: 画板
};

#endif // WIDGET_H
