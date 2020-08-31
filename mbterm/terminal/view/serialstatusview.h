#ifndef SERIALSTATUSVIEW_H
#define SERIALSTATUSVIEW_H

#include <QWidget>
#include <QSerialPort>
#include <QGroupBox>
#include <QLabel>
#include <QLayout>
#include <QTimer>
#include <QVector>

class SerialStatusView : public QWidget
{
    Q_OBJECT
public:
    explicit SerialStatusView(QSerialPort *serial, QWidget *parent = 0);
    ~SerialStatusView();
private:
    QSerialPort *serial;
    QGroupBox *group;
    QVBoxLayout *vlay;
    QGridLayout *glay;
    QVector<QLabel*> listLabel;
    QTimer *timer;
    QString lsxStyleSet;
    QString lsxStyleReset;
signals:
    
public slots:
    void updatePin();
    void setRequestToSendChanged(bool);
    void setBreakEnabledChanged(bool);
};

#endif // SERIALSTATUSVIEW_H
