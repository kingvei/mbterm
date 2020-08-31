#include "senderview.h"
#include <QDebug>

SenderView::SenderView(QWidget *parent) : QWidget(parent)
{
    vlay = new QHBoxLayout;
    btnSend = new QPushButton("send");
    connect(btnSend, SIGNAL(released()), SLOT(sendPackage()));
    lineEdit = new QLineEdit;
    vlay->addWidget(lineEdit);
    vlay->addWidget(btnSend);
    
    sEOF = new SenderEOFView;
    vlay->addWidget(sEOF);
    setLayout(vlay);
}

SenderView::~SenderView()
{
    delete btnSend;
    delete lineEdit;
    delete vlay;
}


void SenderView::sendPackage()
{
    bool status;
    QStringList strList = lineEdit->text().split(" ");
    QStringList::iterator it;
    QByteArray bytes;
    for(it = strList.begin(); it != strList.end(); ++it)
    {
        unsigned int val = (*it).toUInt(&status, 16);
        bytes.append((char)val);
        if(!status)
        {
            qDebug() << "error send";
            return;
        }
    }

    char buff[256];
    int size = bytes.length();
    memset(buff, 0, sizeof(buff));
    memcpy(buff, bytes.toStdString().c_str(), size);
    
    if(sEOF->isCalcCRC())
    {
        size = sEOF->appendCRC(buff, size);
    }
    
    emit send(buff, size);
}
