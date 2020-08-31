#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QTabWidget>

#include "serial/serialmodel.h"
#include "serial/serialview.h"
#include "terminal/terminal.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QSerialPort *serial;
    QTabWidget *tab;
private slots:
    void send(const char *str, int size);
    void readyRead();
};

#endif // MAINWINDOW_H
