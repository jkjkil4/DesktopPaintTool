#include "paintwidget.h"

PaintWidget* PaintWidget::ins = nullptr;

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    //得到桌面大小
    QRect desktopRect = QGuiApplication::primaryScreen()->geometry();
    setGeometry(0, 0, desktopRect.width(), desktopRect.height());

    //初始化图像
    imgBefore = QImage(desktopRect.size(), QImage::Format_ARGB32);
    imgNow = QImage(desktopRect.size(), QImage::Format_ARGB32);
    imgBefore.fill(QColor(0, 0, 0, 0));
    imgNow.fill(QColor(0, 0, 0, 0));

    //设置窗口属性
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SubWindow);
    setAttribute(Qt::WA_TranslucentBackground);

    //设置timerUpdate的属性
    timerUpdate->setSingleShot(true);
    connect(timerUpdate, SIGNAL(timeout()), this, SLOT(update()));
}

void PaintWidget::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        if(procFunc) {  //如果存在图像处理函数
            updateRect = QRect();
            posBefore = ev->pos();
            (*procFunc)(imgNow, posBefore, ev->pos(), 3, updateRect);   //调用图像处理函数
            START_TIMER(timerUpdate, 16);
        }
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *ev) {
    if(ev->buttons() & Qt::LeftButton) {
        if(procFunc) {  //如果存在图像处理函数
            (*procFunc)(imgNow, posBefore, ev->pos(), 3, updateRect);   //调用图像处理函数
            posBefore = ev->pos();
            START_TIMER(timerUpdate, 16);
        }
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        if(procFunc) {  //如果存在图像处理函数
            urImgBefore = imgBefore.copy(updateRect);   //将imgBefore有更新的区域复制到urImgBefore
            urImgNow = imgNow.copy(updateRect); //将imgNow有更新的区域复制到urImgNow
            urToFile(updateRect.topLeft()); //存储ur文件
            jCopyImg(imgBefore, updateRect.topLeft(), imgNow, updateRect);  //使得imgBefore与imgNow相同

            START_TIMER(timerUpdate, 16);
        }
    }
}

void PaintWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), QColor(0, 0, 0, 1));    //绘制一点透明度的矩形，使得窗口能接收到鼠标消息

    //p.drawImage(10, 10, imgBefore);
    p.drawImage(0, 0, imgNow);

#ifdef DEBUG_PAINTWIDGET
    p.setBrush(QColor(255, 255, 255, 200));
    p.drawRect(0, 0, 300, 300);
    QFont font = p.font();
    font.setPointSize(15);
    p.setFont(font);
    p.drawText(QRect(50, 50, 250, 250), Qt::AlignCenter | Qt::AlignVCenter,
               "urIndex:       " + QString::number(urIndex) +
               "\nurIndexMin:    " + QString::number(urIndexMin) +
               "\nurIndexMax:    " + QString::number(urIndexMax));
#endif
}


#define FILE_NAME(index, ur) QString::number(index) + ur
#define FILE_PATH(index, ur) APP_DIR + "/ur/" + FILE_NAME(index, ur)

void PaintWidget::closeEvent(QCloseEvent *) {
    QDir dir(APP_DIR);
    if(!dir.exists("ur")) {
        dir.mkdir("ur");
    }

    if(dir.cd("ur")) {
        //清空所有ur文件
        for(uint i = urIndexMin; i < urIndexMax; i++) {
            dir.remove(FILE_NAME(i, "Before"));
            dir.remove(FILE_NAME(i, "Now"));
        }
        //重置ur属性
        urIndex = 0;
        urIndexMin = 0;
        urIndexMax = 0;
    }
}


void PaintWidget::urToFile(QPoint pos) {
    QDir dir(APP_DIR);
    if(!dir.exists("ur")) {
        dir.mkdir("ur");
    }
    dir.cd("ur");

    for(uint i = urIndex; i < urIndexMax; i++) {    //清空大于或等于urIndex的ur文件
        dir.remove(FILE_NAME(i, "Before"));
        dir.remove(FILE_NAME(i, "Now"));
    }

    //存储undo文件
    QFile fileImgBefore(FILE_PATH(urIndex, "Before"));
    if(fileImgBefore.open(QIODevice::WriteOnly)) {
        QDataStream out(&fileImgBefore);
        out << pos << urImgBefore;
        fileImgBefore.close();
    }

    //存储redo文件
    QFile fileImgNow(FILE_PATH(urIndex, "Now"));
    if(fileImgNow.open(QIODevice::WriteOnly)) {
        QDataStream out(&fileImgNow);
        out << pos << urImgNow;
        fileImgNow.close();
    }

    urIndex++;
    urIndexMax = urIndex;
    //限制ur文件的数量
    if(urIndex - urIndexMin > 100) {
        dir.remove(FILE_NAME(urIndexMin, "Before"));
        dir.remove(FILE_NAME(urIndexMin, "Now"));
        urIndexMin++;
    }

    emit painted();
}

void PaintWidget::undo() {
    if(urIndex <= urIndexMin)
        return;

    urIndex--;

    QFile fileImgBefore(FILE_PATH(urIndex, "Before"));
    if(fileImgBefore.open(QIODevice::ReadOnly)) {
        QDataStream in(&fileImgBefore);
        QPoint pos;
        QImage img;
        in >> pos >> img;
        jCopyImg(imgBefore, pos, img, img.rect());
        jCopyImg(imgNow, pos, img, img.rect());
        fileImgBefore.close();
    }

    START_TIMER(timerUpdate, 16);
}

void PaintWidget::redo() {
    if(urIndex >= urIndexMax)
        return;

    QFile fileImgNow(FILE_PATH(urIndex, "Now"));
    if(fileImgNow.open(QIODevice::ReadOnly)) {
        QDataStream in(&fileImgNow);
        QPoint pos;
        QImage img;
        in >> pos >> img;
        jCopyImg(imgBefore, pos, img, img.rect());
        jCopyImg(imgNow, pos, img, img.rect());
        fileImgNow.close();
    }

    urIndex++;

    START_TIMER(timerUpdate, 16);
}

void PaintWidget::clear() {
    QDir dir(APP_DIR);
    if(!dir.cd("ur"))
        return;

    for(uint i = urIndexMin; i < urIndexMax; i++) {
        dir.remove(FILE_NAME(i, "Before"));
        dir.remove(FILE_NAME(i, "Now"));
    }

    urIndex = 0;
    urIndexMin = 0;
    urIndexMax = 0;

    imgBefore.fill(QColor(0, 0, 0, 0));
    imgNow.fill(QColor(0, 0, 0, 0));

    START_TIMER(timerUpdate, 16);
}

void PaintWidget::btnEnabled(QWidget *widgetUndo, QWidget *widgetRedo) {
    widgetUndo->setEnabled(urIndex > urIndexMin);
    widgetRedo->setEnabled(urIndex < urIndexMax);
}

#undef FILE_NAME
#undef FILE_PATH
