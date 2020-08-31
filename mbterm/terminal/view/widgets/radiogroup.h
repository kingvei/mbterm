#ifndef RADIOGROUP_H
#define RADIOGROUP_H

#include <QWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <QLayout>

#include <QList>

class RadioGroup : public QGroupBox
{
    Q_OBJECT
public:
    explicit RadioGroup(QWidget *parent = 0);
    virtual ~RadioGroup();
    void append(QRadioButton *radio);
private:
    QList<QRadioButton*> listRadio;
    QLayout *vlay;
signals:
    
public slots:
};

#endif // RADIOGROUP_H
