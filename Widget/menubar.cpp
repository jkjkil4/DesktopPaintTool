#include "menubar.h"

#include <QCheckBox>

MenuBar::MenuBar(QWidget *parent) : QWidget(parent)
{
    //创建控件
    StateBtn *foldBtn = new StateBtn(QIcon(":/FoldBtn/Resource/FoldBtn1.png"), QIcon(":/FoldBtn/Resource/FoldBtn2.png"));
    foldBtn->setState(true);
    connect(foldBtn, &StateBtn::stateChanged, [=](bool state){ emit foldStateChanged(state); });

    IconBtn *btnClose = new IconBtn(QIcon(":/Btn/Resource/Close.png"));
    connect(btnClose, &IconBtn::clicked, [=]{ emit wndClose(); });

    //创建布局
    QHBoxLayout *layMain = new QHBoxLayout;
    layMain->setMargin(2);
    layMain->setSpacing(0);
    layMain->addWidget(foldBtn);
    layMain->addStretch();
    layMain->addWidget(btnClose);
    setLayout(layMain);

    //设置属性
    limitHeight(this, 20);
}


void MenuBar::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        mousePosStart = ev->pos();
    }
}

void MenuBar::mouseMoveEvent(QMouseEvent *ev) {
    if(ev->buttons() & Qt::LeftButton) {
        QPoint pos = ev->pos();
        emit wndMoveOffset(pos.x() - mousePosStart.x(), pos.y() - mousePosStart.y());
    }
}

void MenuBar::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setBrush(dotColor);
    p.setPen(Qt::NoPen);
    p.setRenderHint(QPainter::RenderHint::Antialiasing);

    p.fillRect(0, 0, width(), height(), bgColor);

    int dotAreaWidth = (2 * dotRadius + dotSpacing) * (dotCount - 1);
    int xStart = (width() - dotAreaWidth) / 2;
    int yPos = height() / 2;
    repeat(i, dotCount) {
        p.drawEllipse(QPoint(xStart, yPos), dotRadius, dotRadius);
        xStart += 2 * dotRadius + dotSpacing;
    }
}
