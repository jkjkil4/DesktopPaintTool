#ifndef HEADER_H
#define HEADER_H

#include <QWidget>
#include <QPainter>
#include <QDebug>

#define VAR_GET_FUNC(Func, var, Type) Type get##Func() const { return var; }
#define VAR_SET_FUNC(Func, var, Type) void set##Func(const Type &__##var##__) { var = __##var##__; }
#define VAR_FUNC(Func, var, Type) VAR_GET_FUNC(Func, var, Type) VAR_SET_FUNC(Func, var, Type)

#define VAR_SET_FUNC_UPDATE(Func, var, Type) void set##Func(const Type &__##var##__) { var = __##var##__; update(); }
#define VAR_FUNC_UPDATE(Func, var, Type) VAR_GET_FUNC(Func, var, Type) VAR_SET_FUNC_UPDATE(Func, var, Type)


#define repeat(i, n) for(int i = 0; i < n; i++)
#define SC static constexpr
#define START_TIMER(timer, msec) if(!timer->isActive()) timer->start(msec)


inline void limitWidth(QWidget *widget, int w) {
    widget->setMaximumWidth(w);
    widget->setMinimumWidth(w);
}
inline void limitHeight(QWidget *widget, int h) {
    widget->setMaximumHeight(h);
    widget->setMinimumHeight(h);
}
inline void limitSize(QWidget *widget, QSize size) {
    widget->setMaximumSize(size);
    widget->setMinimumSize(size);
}
inline void limitSize(QWidget *widget, int w, int h) {
    widget->setMaximumSize(w, h);
    widget->setMinimumSize(w, h);
}


inline void jDrawRecFrame(QPainter& p, int x, int y, int w, int h, int width, QColor c){
    //顶部
    p.fillRect(x, y, w, width, c);
    //左侧
    p.fillRect(x, y + width, width, h - 2 * width, c);
    //右侧
    p.fillRect(x + w - width, y + width, width, h - 2 * width, c);
    //底部
    p.fillRect(x, y + h - width, w, width, c);
}

#endif // HEADER_H
