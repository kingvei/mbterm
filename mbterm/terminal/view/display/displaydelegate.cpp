#include "displaydelegate.h"

DisplayDelegate::DisplayDelegate()
{
    
}


QString DisplayAsHex0x::getName() const
{
    return "Hex0x";
}

QString DisplayAsHex0x::formatText(const char *data, int size)
{
    QString text = "";
    for(int i = 0; i < size; i++)
    {
        text += QString("0x%1 ").arg(((unsigned char)data[i]) & 0xff, 0, 16);
    }
    return text;
}


QString DisplayAsHex::getName() const
{
    return "Hex";
}

QString DisplayAsHex::formatText(const char *data, int size)
{
    QString text = "";
    for(int i = 0; i < size; i++)
    {
        text += QString("%1 ").arg(((unsigned char)data[i]) & 0xff, 2, 16, QLatin1Char('0')).toUpper();
    }
    return text;
}
