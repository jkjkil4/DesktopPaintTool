#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //创建控件
    MenuBar *menuBar = new MenuBar;
    connect(menuBar, &MenuBar::wndMoveOffset, [=](int xOffset, int yOffset){
        int toX = x() + xOffset, toY = y() + yOffset;
        QRect screenRect =  QGuiApplication::primaryScreen()->availableVirtualGeometry();
        toX = qBound(0, toX, screenRect.width() - width());
        toY = qBound(0, toY, screenRect.height() - height());
        move(toX, toY);
    });
    connect(menuBar, &MenuBar::foldStateChanged, [=](bool state){
        toolsWidget->setVisible(state);
        adjustSize();
    });
    connect(menuBar, &MenuBar::wndClose, [=]{
        int res = QMessageBox::information(this, "提示", "确认要关闭吗", QMessageBox::Yes, QMessageBox::No);
        if(res == QMessageBox::Yes) {
            //TODO: close画板
            close();
        }
    });

    ToolList *toolList = new ToolList;
    connect(toolList, SIGNAL(toolChanged()), toolCursor, SLOT(update()));
    connect(toolCursor, SIGNAL(clicked()), toolList, SLOT(update()));

    limitHeight(toolsWidget, 400);

    //toolsWidget的layout
    QVBoxLayout *layTools = new QVBoxLayout;
    layTools->setMargin(4);
    layTools->setSpacing(2);
    layTools->addWidget(toolCursor);
    layTools->addWidget(toolList, 1);
    toolsWidget->setLayout(layTools);

    //创建布局
    QVBoxLayout *layMain = new QVBoxLayout;
    layMain->setSpacing(0);
    layMain->setMargin(1);
    layMain->addWidget(menuBar);
    layMain->addWidget(toolsWidget);
    setLayout(layMain);

    //设置属性
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    limitWidth(this, 80);
}

Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *) {
    QPainter p(this);

    jDrawRecFrame(p, 0, 0, width(), height(), 1, Qt::gray);
}

