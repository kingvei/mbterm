#include "serialview.h"
#include <QSerialPortInfo>

SerialView::SerialView(SerialModel *serialModel, QWidget *parent) : QWidget(parent)
{
    m_serialModel = serialModel;
    glay = new QGridLayout(this);
    glay->setSpacing(5);
    btnOpen = new QPushButton("Open", this);
    btnClose = new QPushButton("Close", this);
    btnUpdate = new QPushButton("Update", this);
    cbSerialPort = new QComboBox(this);
    cbBaud = new QComboBox(this);
    labelBaud = new QLabel("Baud", this);
    labelPort = new QLabel("Port", this);
    
    portInfo = new QLabel(this);

    createListPort(cbSerialPort);
    connect(btnUpdate, &QPushButton::clicked, [=]{
        cbSerialPort->clear();
        createListPort(cbSerialPort);
    });
    createListBaud(cbBaud);
    
    connect(btnOpen, &QPushButton::released, this, &SerialView::open);
    connect(btnClose, &QPushButton::released, this, &SerialView::close);
    
    connect(cbBaud, qOverload<int>(&QComboBox::currentIndexChanged), this, &SerialView::selectBaud);

    
    int index = cbBaud->findData(serialModel->serialPort()->baudRate());
    if ( index != -1 )
    {
        cbBaud->setCurrentIndex(index);
    }
    
    index = cbSerialPort->findText(serialModel->serialPort()->portName());
    if ( index != -1 )
    {
        cbSerialPort->setCurrentIndex(index);
    }
    connect(cbSerialPort, qOverload<int>(&QComboBox::currentIndexChanged), this, &SerialView::selectSerial);
    
    glay->addWidget(labelPort,      0, 0, 1, 1);
    glay->addWidget(cbSerialPort,   0, 1, 1, 1);
    glay->addWidget(btnUpdate,      1, 0, 1, 2);
    glay->addWidget(labelBaud,      2, 0, 1, 1);
    glay->addWidget(cbBaud,         2, 1, 1, 1);

    RadioGroup<QSerialPort::Parity> *groupParity = new RadioGroup<QSerialPort::Parity>("Parity",
    {{QSerialPort::NoParity, "No"},
     {QSerialPort::OddParity, "Odd"},
     {QSerialPort::EvenParity, "Even"},
     {QSerialPort::MarkParity, "Mark"},
     {QSerialPort::SpaceParity, "Space"}}, this);
    connect(groupParity, &QGroupBox::clicked, [=]{
        serialModel->setParity(groupParity->data());
    });

    RadioGroup<QSerialPort::DataBits> *groupDataBits = new RadioGroup<QSerialPort::DataBits>("Data Bits",
    {{QSerialPort::Data5, "Data 5"},
     {QSerialPort::Data6, "Data 6"},
     {QSerialPort::Data7, "Data 7"},
     {QSerialPort::Data8, "Data 8"}}, this);
    connect(groupDataBits, &QGroupBox::clicked, [=]{
        serialModel->setDataBits(groupDataBits->data());
    });

    RadioGroup<QSerialPort::FlowControl> *groupFlowControl = new RadioGroup<QSerialPort::FlowControl>("Flow Control",
    {{QSerialPort::NoFlowControl, "None"},
     {QSerialPort::HardwareControl, "RTS/CTS"},
     {QSerialPort::SoftwareControl, "XON/XOFF"}}, this);
    connect(groupFlowControl, &QGroupBox::clicked, [=]{
        serialModel->setFlowControl(groupFlowControl->data());
        groupFlowControl->data();
    });

    RadioGroup<QSerialPort::StopBits> *groupStopBits = new RadioGroup<QSerialPort::StopBits>("Stop Bits",
    {{QSerialPort::OneStop, "1 stop"},
     {QSerialPort::OneAndHalfStop, "1.5 stop"},
     {QSerialPort::TwoStop, "2 stop"}}, this);
    connect(groupStopBits, &QGroupBox::clicked, [=]{
        serialModel->setStopBits(groupStopBits->data());
    });

    glay->addWidget(groupParity);
    glay->addWidget(groupDataBits);
    glay->addWidget(groupFlowControl);
    glay->addWidget(groupStopBits);

    groupParity->setMaximumSize(100, 200);
    groupDataBits->setMaximumSize(100, 200);
    groupFlowControl->setMaximumSize(100, 200);
    groupStopBits->setMaximumSize(100, 200);

    groupParity->setData(serialModel->serialPort()->parity());
    groupDataBits->setData(serialModel->serialPort()->dataBits());
    groupFlowControl->setData(serialModel->serialPort()->flowControl());
    groupStopBits->setData(serialModel->serialPort()->stopBits());

    glay->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    glay->addWidget(btnOpen);
    glay->addWidget(btnClose);
    glay->addWidget(portInfo, 10, 0, 1, 10);

    setLayout(glay);
    if(serialModel->serialPort()->isOpen())
        open();
}

SerialView::~SerialView()
{
}

void SerialView::createListPort(QComboBox *combobox)
{
    QList<QSerialPortInfo> listPort = QSerialPortInfo::availablePorts();
    QList<QSerialPortInfo>::iterator it;
    for(it = listPort.begin(); it != listPort.end(); ++it)
    {
        combobox->addItem(it->portName());
    }
}

void SerialView::createListBaud(QComboBox *combobox)
{
    QList<qint32> _listBaud= QSerialPortInfo::standardBaudRates();
    QList<qint32>::iterator itb;
    for(itb = _listBaud.begin(); itb != _listBaud.end(); ++itb)
    {
        combobox->addItem(QString::number(*itb), *itb);
    }
    
}

void SerialView::selectBaud(int index)
{
    int baud = cbBaud->itemData(index).toInt();
    m_serialModel->setBaudRate(baud);
}

void SerialView::selectSerial(int index)
{
    QSerialPortInfo sp(cbSerialPort->itemText(index));
    close();
    m_serialModel->setPort(sp);
}

void SerialView::open()
{
    QSerialPortInfo sp(cbSerialPort->currentText());
    m_serialModel->setPort(sp);
    m_serialModel->open(QIODevice::ReadWrite);
    QSerialPort *port = m_serialModel->serialPort();
    QString str;
    QTextStream out(&str);
    out << port->portName();
    out << " isOpen:";
    out << (port->isOpen() ? "true" : "false");
    out << " baud:" << port->baudRate();
    portInfo->setText(str);
}

void SerialView::close()
{
    m_serialModel->close();
    QSerialPort *port = m_serialModel->serialPort();
    QString str;
    QTextStream out(&str);
    out << port->portName();
    out << " isOpen:";
    out << (port->isOpen() ? "true" : "false");
    out << " baud:" << port->baudRate();
    portInfo->setText(str);
}
