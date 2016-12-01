#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Music");
    w.setWindowFlags(Qt::FramelessWindowHint);
//    w.setAttribute(Qt::WA_TranslucentBackground);
    w.show();

    return a.exec();
}
