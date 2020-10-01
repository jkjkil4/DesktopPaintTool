#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>

#include <QGuiApplication>
#include <QScreen>
#include <QPainter>

class PaintWidget : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *) override;

public:
    PaintWidget(QWidget *parent = nullptr);
    ~PaintWidget() override = default;

    static PaintWidget *ins;

private:
    QImage imgBefore, imgNow;
};

#endif // PAINTWIDGET_H
