#include "mainwindow.h"
#include <QDebug>

#include <QtQuick/QQuickView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    tab = new QTabWidget;

    serial = new QSerialPort;
    SerialModel *sm = new SerialModel(serial);
    SerialView *sv = new SerialView(sm);
    


    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readyRead);
    Terminal *terminal = new Terminal(serial);

    
    tab->addTab(sv, "Settings");

    tab->addTab(terminal->view(), "Terminal");

    setCentralWidget(tab);

}

MainWindow::~MainWindow()
{
    delete tab;
    serial->close();
    delete serial;
}

void MainWindow::send(const char *str, int size)
{
    serial->write(str, size);
    qDebug() << str;
    
}

void MainWindow::readyRead()
{
    QByteArray reseive = serial->readAll();
}
