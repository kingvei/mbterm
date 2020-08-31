#ifndef TERMINAL_H
#define TERMINAL_H

#include <QObject>

#include "view/consoleview.h"
#include "view/consoledisplayview.h"
#include "view/senderview.h"
#include "view/serialstatusview.h"

class Terminal : public QObject
{
    Q_OBJECT
public:
    explicit Terminal(QSerialPort *serial, QObject *parent = nullptr);
    QWidget *view(void){return m_view;};
private:
    ConsoleView *cv;
    SerialStatusView *ssv;
    QWidget *m_view;
    QSerialPort *m_serial;
public slots:
    void send(const char *str, int size);
    void readyRead(void);
};

#endif // TERMINAL_H
