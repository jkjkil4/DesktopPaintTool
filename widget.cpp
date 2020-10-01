#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //创建控件
    PaintWidget::ins = paintWidget;
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
        close();
    });

    ToolList *toolList = new ToolList;
    connect(toolList, &ToolList::toolChanged, [=]{
        if(!paintWidget->isVisible()) {
            toolCursor->update();
            paintWidget->setVisible(true);
            setParent(paintWidget);
            setVisible(true);
        }
    });
    connect(toolCursor, &ToolCursor::clicked, [=]{
        if(paintWidget->isVisible()) {
            toolList->update();
            paintWidget->setVisible(false);
            setParent(nullptr);
            setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SubWindow);
            setAttribute(Qt::WA_QuitOnClose);
            setVisible(true);
        }
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
    adjustSize();
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SubWindow);
    setAttribute(Qt::WA_QuitOnClose);
    limitWidth(this, 80);
}

Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *) {
    QPainter p(this);

    p.fillRect(1, 1, width() - 2, height() - 2, QColor(240, 240, 240));
    jDrawRecFrame(p, 0, 0, width(), height(), 1, Qt::gray);
}

void Widget::closeEvent(QCloseEvent *ev) {
    int res = QMessageBox::information(this, "提示", "确认要关闭吗", "确认", "取消");
    if(res == 0) {
        paintWidget->close();
    } else {
        ev->ignore();
    }
}

