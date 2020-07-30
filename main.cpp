#include "include/mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <cstdio>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QDesktopWidget *desktop = QApplication::desktop();
    //int screen_count = desktop->screenCount();

    MainWindow w;

    w.setWindowState(Qt::WindowFullScreen);
    w.showFullScreen();
    //w.show();
    return a.exec();
}
