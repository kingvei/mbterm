#ifndef DISPLAYDELEGATE_H
#define DISPLAYDELEGATE_H

#include <QObject>
#include <QDebug>

class DisplayDelegate
{
public:
    DisplayDelegate();
    
    virtual QString getName() const = 0;
    virtual QString formatText(const char* data, int size) = 0;
private:
    
};

class DisplayAsHex : public DisplayDelegate
{    
    // DisplayDelegate interface
public:
    virtual QString getName() const;
    virtual QString formatText(const char *data, int size);
};

class DisplayAsHex0x : public DisplayDelegate
{
    // DisplayDelegate interface
public:
    virtual QString getName() const;
    virtual QString formatText(const char *data, int size);
};

class DisplayAsASCII : public DisplayDelegate
{    
public:
    virtual QString getName() const
    {
        return "ASCII";
    }
    
    virtual QString formatText(const char *data, int size)
    {
        QString text = "";
        for(int i = 0; i < size; i++)
        {
           
            text += QString(data[i]);
        }
        return text;
    }
};

class DisplayAsUINT8 : public DisplayDelegate
{    
public:
    virtual QString getName() const
    {
        return "UINT8";
    }
    
    virtual QString formatText(const char *data, int size)
    {
        
        QString text = "";
        for(int i = 0; i < size; i++)
        {
            text += QString("%1 ").arg(((unsigned char)data[i]) & 0xff, 0, 10);
        }
        return text;
    }
};

class DisplayAsBinary : public DisplayDelegate
{    
public:
    virtual QString getName() const
    {
        return "Binary";
    }
    
    virtual QString formatText(const char *data, int size)
    {
        
        QString text = "";
        for(int i = 0; i < size; i++)
        {
             text += QString("%1 ").arg(((unsigned char)data[i]) & 0xff, 0, 2);
        }
        return text;
    }
};


#endif // DISPLAYDELEGATE_H
