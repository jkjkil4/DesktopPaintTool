#include "paintwidget.h"

PaintWidget* PaintWidget::ins = nullptr;

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    QRect desktopRect = QGuiApplication::primaryScreen()->geometry();
    setGeometry(0, 0, desktopRect.width(), desktopRect.height());

    imgBefore = QImage(desktopRect.size(), QImage::Format_ARGB32);
    imgNow = QImage(desktopRect.size(), QImage::Format_ARGB32);
    imgBefore.fill(QColor(0, 0, 0, 0));
    imgNow.fill(QColor(0, 0, 0, 0));

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SubWindow);
    setAttribute(Qt::WA_TranslucentBackground);

    timerUpdate->setSingleShot(true);
    connect(timerUpdate, SIGNAL(timeout()), this, SLOT(update()));
}

void PaintWidget::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        if(procFunc) {
            updateRect = QRect();
            posBefore = ev->pos();
            (*procFunc)(imgNow, posBefore, ev->pos(), 4, updateRect);
            START_TIMER(timerUpdate, 16);
        }
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *ev) {
    if(ev->buttons() & Qt::LeftButton) {
        if(procFunc) {
            (*procFunc)(imgNow, posBefore, ev->pos(), 4, updateRect);
            posBefore = ev->pos();
            START_TIMER(timerUpdate, 16);
        }
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        QPainter p(&imgBefore);
        p.drawImage(updateRect, imgNow, updateRect);
        START_TIMER(timerUpdate, 16);
    }
}

void PaintWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), QColor(0, 0, 0, 1));

    //p.drawImage(0, 0, imgNow);
    p.drawImage(0, 0, imgNow);
}


#define FILE_NAME(index, ur) QString::number(index) + ur
#define FILE_PATH(index, ur) APP_DIR + "/ur/" + FILE_NAME(index, ur)

void PaintWidget::closeEvent(QCloseEvent *) {
    QDir dir(APP_DIR);
    if(!dir.exists("ur")) {
        dir.mkdir("ur");
    }

    if(dir.cd("ur")) {
        for(uint i = 0; i < urIndexMax; i++) {
            dir.remove(FILE_NAME(i, "Before"));
            dir.remove(FILE_NAME(i, "Now"));
        }
    }
}

void PaintWidget::drawImageToImage(QImage &targetImg, const QImage &img, QPoint pos) {
    int imgWidth = img.width();
    int imgHeight = img.height();
    int posX = pos.x();
    int posY = pos.y();
    for(int j = 0; j < imgHeight; j++) {
        for(int i = 0; i < imgWidth; i++) {
            targetImg.setPixel(i + posX, j + posY, img.pixel(i, j));
        }
    }
}

void PaintWidget::urToFile(QPoint pos) {
    QDir dir(APP_DIR);
    if(!dir.exists("ur")) {
        dir.mkdir("ur");
    }

    if(urIndex < urIndexMax) {
        if(dir.cd("ur")) {
            for(uint i = urIndex; i < urIndexMax; i++) {
                dir.remove(FILE_NAME(i, "Before"));
                dir.remove(FILE_NAME(i, "Now"));
            }
        }
    }

    QFile fileImgBefore(FILE_PATH(urIndex, "Before"));
    if(fileImgBefore.open(QIODevice::WriteOnly)) {
        QDataStream out(&fileImgBefore);
        out << pos << urImgBefore;
        fileImgBefore.close();
    }

    QFile fileImgNow(FILE_PATH(urIndex, "Now"));
    if(fileImgNow.open(QIODevice::WriteOnly)) {
        QDataStream out(&fileImgNow);
        out << pos << urImgNow;
        fileImgNow.close();
    }

    urIndex++;
    urIndexMax = urIndex;
}

void PaintWidget::undo() {
    if(urIndex <= 0)
        return;

    urIndex--;

    QFile fileImgBefore(FILE_PATH(urIndex, "Before"));
    if(fileImgBefore.open(QIODevice::ReadOnly)) {
        QDataStream in(&fileImgBefore);
        QPoint pos;
        QImage img;
        in >> pos >> img;
        drawImageToImage(imgBefore, img, pos);
        drawImageToImage(imgNow, img, pos);
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
        drawImageToImage(imgBefore, img, pos);
        drawImageToImage(imgNow, img, pos);
    }

    urIndex++;

    START_TIMER(timerUpdate, 16);
}

#undef FILE_NAME
#undef FILE_PATH
