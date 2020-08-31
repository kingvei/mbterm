#include "serialmodel.h"

SerialModel::SerialModel(QSerialPort *serialPort, QObject *parent) : 
    m_serialPort(serialPort), m_settings(QSettings::IniFormat, QSettings::UserScope,
                                         QLatin1String("mbterm"),
                                         QLatin1String("serialconfig"))
{
    m_settings.beginGroup("SERIAL");
    setPort( QSerialPortInfo( m_settings.value("Port", "COM1").toString()));
    setBaudRate( m_settings.value("BaudRate", 115200).toUInt());
    setDataBits(m_settings.value("DataBits", QSerialPort::Data8).value<QSerialPort::DataBits>());
    setFlowControl(m_settings.value("FlowControl", QSerialPort::NoFlowControl).value<QSerialPort::FlowControl>());
    setParity(m_settings.value("Parity", QSerialPort::NoParity).value<QSerialPort::Parity>());
    setStopBits( m_settings.value("StopBits", QSerialPort::OneStop).value<QSerialPort::StopBits>());
    bool isOpen = m_settings.value("isOpen", false).toBool();
    m_settings.endGroup();
    if(isOpen)
    {
        open(QSerialPort::ReadWrite);
    }

}

SerialModel::~SerialModel()
{
    m_serialPort->close();
}

bool SerialModel::setBaudRate(qint32 baudRate, QSerialPort::Directions directions)
{
    return m_serialPort->setBaudRate(baudRate, directions);
}

bool SerialModel::setDataBits(QSerialPort::DataBits dataBits)
{
    return m_serialPort->setDataBits(dataBits);
}

bool SerialModel::setFlowControl(QSerialPort::FlowControl flowControl)
{
    return m_serialPort->setFlowControl(flowControl);
}

bool SerialModel::setParity(QSerialPort::Parity parity)
{
    return m_serialPort->setParity(parity);
}

bool SerialModel::setStopBits(QSerialPort::StopBits stopBits)
{
    return m_serialPort->setStopBits(stopBits);
}

void SerialModel::setPort(const QSerialPortInfo &serialPortInfo)
{
    m_serialPort->setPort(serialPortInfo);
}

bool SerialModel::open(QIODevice::OpenMode mode)
{
    m_settings.beginGroup("SERIAL");
    m_settings.setValue("isOpen", true);
    m_settings.setValue("DataBits", m_serialPort->dataBits());
    m_settings.setValue("Port", m_serialPort->portName());
    m_settings.setValue("FlowControl", m_serialPort->flowControl());
    m_settings.setValue("BaudRate", m_serialPort->baudRate());
    m_settings.setValue("Parity", m_serialPort->parity());
    m_settings.setValue("StopBits", m_serialPort->stopBits());
    m_settings.endGroup();
    return m_serialPort->open(mode);
}

void SerialModel::close()
{
    m_settings.beginGroup("SERIAL");
    m_settings.setValue("isOpen", false);
    m_settings.endGroup();
    m_serialPort->close();
}

QSerialPort *SerialModel::serialPort()
{
    return m_serialPort;
}


