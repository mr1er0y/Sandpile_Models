#include "mainwindow.h"

#include <QApplication>
#include <QImage>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Sandpile model");
    w.show();
    return a.exec();
}
