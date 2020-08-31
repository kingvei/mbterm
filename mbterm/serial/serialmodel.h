#ifndef SERIALMODEL_H
#define SERIALMODEL_H

#include <QtSerialPort/QtSerialPort>
#include <QSettings>
class SerialModel
{
public:
    SerialModel(QSerialPort *serialPort, QObject *parent = Q_NULLPTR);
    virtual ~SerialModel();
    
    bool setBaudRate(qint32 baudRate, QSerialPort::Directions directions = QSerialPort::AllDirections);
    bool setDataBits(QSerialPort::DataBits dataBits);
    bool setFlowControl(QSerialPort::FlowControl flowControl);
    bool setParity(QSerialPort::Parity parity);
    bool setStopBits(QSerialPort::StopBits stopBits);
    void setPort(const QSerialPortInfo &serialPortInfo);
    
    bool open(QSerialPort::OpenMode mode);
    void close();
    QSerialPort *serialPort();
    

private:
    QSerialPort *m_serialPort;
    QSettings m_settings;
};

#endif // SERIALMODEL_H
