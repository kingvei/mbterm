#ifndef SERIALVIEW_H
#define SERIALVIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QLayout>
#include <QRadioButton>
#include <QGroupBox>
#include <QList>

#include "serialmodel.h"

template <typename ENUM_T>
class RadioGroup : public QGroupBox
{
public:
    RadioGroup(QString name, QMap<ENUM_T, QString> aliases, QWidget *parent = nullptr) : QGroupBox(name, parent){
        m_aliases = aliases;
        QVBoxLayout *vbox = new QVBoxLayout(this);
        for(QString it : aliases)
        {
            auto radio = new QRadioButton(it, this);
            m_buttons.insert(radio, aliases.key(it));
            vbox->addWidget(radio);
            vbox->setAlignment(Qt::AlignTop | Qt::AlignLeft);
            connect(radio, &QRadioButton::clicked, this, &QGroupBox::clicked);
        }
        vbox->setSpacing(2);
        vbox->addStretch(1);
        setLayout(vbox);
    };
    ~RadioGroup(){};
    ENUM_T data()
    {
        for(auto it : m_buttons)
            if(m_buttons.key(it)->isChecked())
                return it;
    }
    void setData(ENUM_T data)
    {
        for(auto it : m_buttons)
        {
            if(data == it)
            {
                m_buttons.key(it)->setChecked(true);
            }
        }
    }
private:
    QMap<QRadioButton*, ENUM_T> m_buttons;
    QMap<ENUM_T, QString> m_aliases;
};

class SerialView : public QWidget
{
    Q_OBJECT
public:
    explicit SerialView(SerialModel *serialModel, QWidget *parent = nullptr);
    virtual ~SerialView();
private:
    void createListPort(QComboBox *combobox);
    void createListBaud(QComboBox *combobox);
private:
    SerialModel *m_serialModel = nullptr;
    QGridLayout *glay;
    QComboBox *cbSerialPort;
    QComboBox *cbBaud;
    QLabel *labelPort;
    QLabel *labelBaud;
    
    QPushButton *btnOpen;
    QPushButton *btnClose;
    QPushButton *btnUpdate;
    QGroupBox *groupParity;
    QGroupBox *groupDataBits;
    QGroupBox *groupFlowControl;
    QGroupBox *groupStopBits;

    QLabel *portInfo;
signals:
    
public slots:
    void selectBaud(int index);
    void selectSerial(int index);
    
    void open();
    void close();
};

#endif // SERIALVIEW_H
