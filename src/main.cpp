#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QSplashScreen>

#include <windows.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile f(":/qdarkstyle/dark/darkstyle.qss");
    f.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts(&f);
    qApp->setStyleSheet(ts.readAll());

    QPixmap pixmap(":/icons/splash.jpg");
    QSplashScreen splash(pixmap);
    splash.show();
    QApplication::processEvents();
    Sleep(1000);

    /// ask for retrieving the last session instead of using sleep

    MainWindow w;
    w.show();
    splash.finish(&w);
    return a.exec();
}
