#include "radiogroup.h"

RadioGroup::RadioGroup(QWidget *parent) : QGroupBox(parent)
{
    vlay = new QHBoxLayout;
    setLayout(vlay);
}

RadioGroup::~RadioGroup()
{
    
}

void RadioGroup::append(QRadioButton *radio)
{
    listRadio.append(radio);
    vlay->addWidget(radio);
}
