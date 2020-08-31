#include "serialstatusview.h"
#include <QDebug>

SerialStatusView::SerialStatusView(QSerialPort *serial, QWidget *parent) : 
    QWidget(parent),
    serial(serial)
{
    connect(serial, SIGNAL(requestToSendChanged(bool)), SLOT(setRequestToSendChanged(bool)));
    
    QSerialPort::PinoutSignals pin;
    //pin = serial->pinoutSignals();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePin()));
    timer->start(10);
    
    vlay = new QVBoxLayout();
    glay = new QGridLayout();
    group = new QGroupBox();
    
    
    QSize lsxSize(12, 12);
    lsxStyleReset = "background-color: yellow;"
                    "border-style: outset;" 
                    "border-color: black;"
                    "border-width: 1px;";
    
    lsxStyleSet = "background-color: green;"
                  "border-style: outset;" 
                  "border-color: black;"
                  "border-width: 1px;";
    
    QStringList strList;    
    strList.append("Rx");
    strList.append("Tx");
    strList.append("DTR");
    strList.append("DCD");
    strList.append("DSR");
    strList.append("RNG");
    strList.append("RST");
    strList.append("CST");
    strList.append("STD");
    strList.append("SRD");
    strList.append("Break");
    
    QStringList ::iterator it;
    
    int x = 0;
    for(it = strList.begin(); it != strList.end(); ++it)
    {
        QLabel *l1 = new QLabel(*it);
        QLabel *ls1 = new QLabel();
        ls1->setMinimumSize(lsxSize);
        ls1->setMaximumSize(lsxSize);
        ls1->setStyleSheet(lsxStyleReset);
        listLabel.push_back(ls1);
        
        glay->addWidget(ls1, x, 0, 1, 1);
        glay->addWidget(l1, x++, 1, 1, 1);
    }
    
    
    glay->setAlignment(Qt::AlignTop);
    group->setLayout(glay);
    
    vlay->addWidget(group);
    
    setLayout(vlay);
}

SerialStatusView::~SerialStatusView()
{
    timer->stop();
    delete timer;
    QVector<QLabel*>::iterator it;
    for(it = listLabel.begin(); it != listLabel.end(); ++it)
    {
        delete *it;
    }
    delete glay;
    delete group;
    delete vlay;
}

void SerialStatusView::updatePin()
{
    QSerialPort::PinoutSignals pin;
    pin = serial->pinoutSignals();
    for(int i = 0; i < 10; i++)
    {
        int s = (pin >> i) & 0x1;
        if(s)
        {
            listLabel[i]->setStyleSheet(lsxStyleSet);
        }
        else
        {
            listLabel[i]->setStyleSheet(lsxStyleReset);
        }
    }
    if(serial->isBreakEnabled())
    {
        listLabel[10]->setStyleSheet(lsxStyleSet);
    }
    else
    {
        listLabel[10]->setStyleSheet(lsxStyleReset);
    }
}

void SerialStatusView::setRequestToSendChanged(bool state)
{
    Q_UNUSED(state);
    updatePin();
}

void SerialStatusView::setBreakEnabledChanged(bool state)
{
    Q_UNUSED(state);
    qDebug() << state;
}

