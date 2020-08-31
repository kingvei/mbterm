#include "terminal.h"

#include <QVBoxLayout>
#include <QLayout>
Terminal::Terminal(QSerialPort *serial, QObject *parent) : QObject(parent)
{
    m_serial = serial;
    QLayout *vlay = new QVBoxLayout;
    m_view = new QWidget;
    m_view->setLayout(vlay);
    QList<QWidget*> listWdgt;
    ssv = new SerialStatusView(serial);
    listWdgt.append(ssv);
    cv = new ConsoleView(&listWdgt);
    SenderView *cdv = new SenderView;
    vlay->addWidget(cv);
    vlay->addWidget(cdv);

    connect(cdv, &SenderView::send, this, &Terminal::send);
    connect(m_serial, &QSerialPort::readyRead, this, &Terminal::readyRead);
}

void Terminal::send(const char *str, int size)
{
    m_serial->write(str, size);
    cv->putByteArray(str, size, "#00ff00");

}

void Terminal::readyRead()
{
    QByteArray reseive = m_serial->readAll();
    cv->putByteArray(reseive, "#ffff00");
}
