#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //创建控件
    PaintWidget::ins = paintWidget;
    paintWidget->setVisible(false);
    MenuBar *menuBar = new MenuBar;
    QWidget *centralWidget = new QWidget;
    connect(menuBar, &MenuBar::wndMoveOffset, [=](int xOffset, int yOffset){
        int toX = x() + xOffset, toY = y() + yOffset;
        QRect screenRect =  QGuiApplication::primaryScreen()->availableVirtualGeometry();
        toX = qBound(0, toX, screenRect.width() - width());
        toY = qBound(0, toY, screenRect.height() - height());
        move(toX, toY);
    });
    connect(menuBar, &MenuBar::foldStateChanged, [=](bool state){
        centralWidget->setVisible(state);
        adjustSize();
    });
    connect(menuBar, &MenuBar::wndClose, [=]{
        close();
    });

    PushButton *btnAbout = new PushButton(QIcon(":/Btn/Resource/About.png"), "关于");
    PushButton *btnUndo = new PushButton(QIcon(":/Btn/Resource/Undo.png"), "撤销");
    btnUndo->setShortcut(QKeySequence("Ctrl+Z"));
    PushButton *btnRedo = new PushButton(QIcon(":/Btn/Resource/Redo.png"), "重做");
    btnRedo->setShortcut(QKeySequence("Ctrl+Y"));
    PushButton *btnClear = new PushButton(QIcon(":/Btn/Resource/Clear.png"), "清空");
    btnClear->setColor2(QColor(250, 180, 180));
    connect(paintWidget, &PaintWidget::painted, [=]{ paintWidget->btnEnabled(btnUndo, btnRedo); });
    connect(btnAbout, &PushButton::clicked, [=]{
        QMenu menu;

        QAction actAbout("关于");
        menu.addAction(&actAbout);
        QAction actAboutQt("关于Qt");
        menu.addAction(&actAboutQt);

        menu.move(cursor().pos());
        QAction *res = menu.exec();

        if(res == &actAbout) {
            QMessageBox::about(this, "关于",
                               "作者: jkjkil4<br>"
                               "github: <a href=https://github.com/jkjkil4/DesktopPaintTool>https://github.com/jkjkil4/DesktopPaintTool</a><br>"
                               "反馈问题: jkjkil@qq.com");
        } else if(res == &actAboutQt) {
            QMessageBox::aboutQt(this);
        }
    });
    connect(btnUndo, &PushButton::clicked, [=]{
        paintWidget->undo();
        paintWidget->btnEnabled(btnUndo, btnRedo);
    });
    connect(btnRedo, &PushButton::clicked, [=]{
        paintWidget->redo();
        paintWidget->btnEnabled(btnUndo, btnRedo);
    });
    connect(btnClear, &PushButton::clicked, [=]{
        paintWidget->clear();
        paintWidget->btnEnabled(btnUndo, btnRedo);
    });
    btnUndo->setEnabled(false);
    btnRedo->setEnabled(false);
    btnClear->setEnabled(false);

    ToolList *toolList = new ToolList;
    connect(toolList, &ToolList::toolChanged, [=]{
        if(!paintWidget->isVisible()) {
            toolCursor->update();
            paintWidget->setVisible(true);
            setParent(paintWidget);
            setVisible(true);
            paintWidget->btnEnabled(btnUndo, btnRedo);
            btnClear->setEnabled(true);
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
            btnUndo->setEnabled(false);
            btnRedo->setEnabled(false);
            btnClear->setEnabled(false);
        }
    });

    limitHeight(centralWidget, 400);

    //创建布局
    QVBoxLayout *layCentral = new QVBoxLayout;
    layCentral->setMargin(4);
    layCentral->setSpacing(2);
    layCentral->addWidget(btnAbout);
    layCentral->addSpacing(4);
    layCentral->addWidget(btnUndo);
    layCentral->addWidget(btnRedo);
    layCentral->addSpacing(4);
    layCentral->addWidget(btnClear);
    layCentral->addSpacing(4);
    layCentral->addWidget(toolCursor);
    layCentral->addWidget(toolList, 1);
    centralWidget->setLayout(layCentral);

    QVBoxLayout *layMain = new QVBoxLayout;
    layMain->setSpacing(0);
    layMain->setMargin(1);
    layMain->addWidget(menuBar);
    layMain->addWidget(centralWidget);
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

