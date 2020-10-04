#include "widget.h"
#include <QApplication>
#include <QSharedMemory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSharedMemory sharedMem;
    sharedMem.setKey(QString("J_DesktopPaintTool_SharedMem"));
    if(sharedMem.attach()){
        QMessageBox::information(nullptr, "提示", "程序正在运行");
        return 0;
    }

    if(sharedMem.create(1)) {
        Widget w;
        w.show();

        return a.exec();
    }

    return 0;
}
