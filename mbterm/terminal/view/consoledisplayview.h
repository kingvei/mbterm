#ifndef CONSOLEDISPLAYVIEW_H
#define CONSOLEDISPLAYVIEW_H

#include <QWidget>
#include <QRadioButton>
#include <QGroupBox>
#include <QLayout>
#include <QList>
#include "display/displaydelegate.h"

class RadioDisplayAs : public QRadioButton
{
    Q_OBJECT
public:
    RadioDisplayAs(QString name, DisplayDelegate *display, QWidget *parent = 0) : 
        QRadioButton(name, parent), 
        dsp(display)
    {
        connect(this, SIGNAL(released()), SLOT(_released()));
    }
    
    DisplayDelegate *getDisplayDelegate()
    {
        return dsp;
    }
private:
    DisplayDelegate *dsp;
private slots:
    void _released()
    {
        emit released(dsp);
    }

signals:
    void released(DisplayDelegate *dsp);
};

class ConsoleDisplayView : public QWidget
{
    Q_OBJECT
public:
    explicit ConsoleDisplayView(QWidget *parent = 0);
    ~ConsoleDisplayView();
    DisplayDelegate* delegate(void);
private:
    QLayout *vlay;
    QLayout *vGroupLay;
    QGroupBox *groupBox;
    QList<QRadioButton*> listButton;
    QList<DisplayDelegate *> listDsp;
signals:
    void released(DisplayDelegate *dsp);
private slots:
    void radioDisplay();
    void radioReleased(DisplayDelegate *dsp);
public slots:
};

#endif // CONSOLEDISPLAYVIEW_H
