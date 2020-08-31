#include "consoledisplayview.h"

ConsoleDisplayView::ConsoleDisplayView(QWidget *parent) : QWidget(parent)
{
    vlay = new QHBoxLayout;
    vGroupLay = new QVBoxLayout;
    groupBox = new QGroupBox;
    
    listDsp.append(new DisplayAsHex());
    listDsp.append(new DisplayAsASCII());
    listDsp.append(new DisplayAsUINT8());
    listDsp.append(new DisplayAsBinary());
    
    QList<DisplayDelegate *>::iterator it;
    
    RadioDisplayAs *radio;
    for(it = listDsp.begin(); it != listDsp.end(); ++it)
    {
        radio = new RadioDisplayAs((*it)->getName(), *it);
        listButton.append(radio);
        vGroupLay->addWidget(radio);
        connect(radio, SIGNAL(released(DisplayDelegate*)), SLOT(radioReleased(DisplayDelegate*)));
    }
    listButton.at(0)->setChecked(true);
    vGroupLay->setAlignment(Qt::AlignTop);
    groupBox->setLayout(vGroupLay);
    vlay->addWidget(groupBox);

    setLayout(vlay);
}

ConsoleDisplayView::~ConsoleDisplayView()
{
    QList<QRadioButton*>::iterator it;
    for(it = listButton.begin(); it != listButton.end(); ++it)
    {
        delete *it;
    }
    delete vGroupLay;
    delete groupBox;
    delete vlay;
}

void ConsoleDisplayView::radioDisplay()
{
    
}

void ConsoleDisplayView::radioReleased(DisplayDelegate *dsp)
{
    emit released(dsp);
}

DisplayDelegate* ConsoleDisplayView::delegate(void)
{
    for(int i = 0; i < listButton.size(); i++)
        if(listButton.at(i)->isChecked())
            return listDsp.at(i);
    return listDsp.at(0);
}
