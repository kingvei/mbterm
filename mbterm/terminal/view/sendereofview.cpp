#include "sendereofview.h"
#include "../crc/crc16.h"
SenderEOFView::SenderEOFView(QWidget *parent) : QWidget(parent)
{
    vlay = new QHBoxLayout;
    cbCheckCRC = new QCheckBox("+crc");
    cbCheckLF = new QCheckBox("+LF");
    cbCheckCR = new QCheckBox("+CR");
    cbTypeCRC = new QComboBox;
    QStringList strList;
    strList << "Modbus16";//<< "Checksum8" << "Checksum16";
    cbTypeCRC->addItems(strList);
    
    vlay->addWidget(cbCheckCR);
    vlay->addWidget(cbCheckLF);
    vlay->addWidget(cbCheckCRC);
    vlay->addWidget(cbTypeCRC);
    setLayout(vlay);
}

SenderEOFView::~SenderEOFView()
{
    delete cbTypeCRC;
    delete cbCheckCRC;
    delete vlay;
}

int SenderEOFView::appendCRC(char *data, int size)
{
    uint8_t data2[size];
    memcpy(data2, data, size);
    uint16_t crc = CRC::GetCRC16(data2, size);
    data[size] = (crc);
    data[size + 1] = (crc >> 8);
    return size +2;
}

bool SenderEOFView::isCalcCRC()
{
    return cbCheckCRC->isChecked();
}
