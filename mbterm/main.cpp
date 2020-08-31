#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    MainWindow w;
    QApplication::setStyle(QStyleFactory::create("windowsvista"));
    w.show();
    
    return a.exec();
}
