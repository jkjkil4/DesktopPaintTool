#include "statebtn.h"

StateBtn::StateBtn(const QIcon &icon1, const QIcon &icon2)
    : icon1(icon1), icon2(icon2)
{
    connect(this, &StateBtn::clicked, [=]{
        state = !state;
        update();
        emit stateChanged(state);
    });

    limitSize(this, QSize(16, 16));
}


void StateBtn::paintEvent(QPaintEvent *) {
    QPainter p(this);
    //p.fillRect(0, 0, width(), height(), Qt::green);

    (state ? icon2 : icon1).paint(&p, QRect(0, 0, width(), height()));
}
