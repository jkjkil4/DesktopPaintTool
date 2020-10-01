#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //创建控件
    paintWidget->setVisible(false);
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
        int res = QMessageBox::information(this, "提示", "确认要关闭吗", "确认", "取消");
        if(res == 0) {
            paintWidget->close();
            close();
        }
    });

    ToolList *toolList = new ToolList;
    connect(toolList, &ToolList::toolChanged, [=]{
        toolCursor->update();
        paintWidget->setVisible(true);
        setParent(paintWidget);
        setVisible(true);
    });
    connect(toolCursor, &ToolCursor::clicked, [=]{
        toolList->update();
        paintWidget->setVisible(false);
        setParent(nullptr);
        setVisible(true);
    });

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

