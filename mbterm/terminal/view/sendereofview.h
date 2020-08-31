#ifndef SENDEREOFVIEW_H
#define SENDEREOFVIEW_H

#include <QWidget>
#include <QLayout>
#include <QComboBox>
#include <QCheckBox>



class SenderEOFView : public QWidget
{
    Q_OBJECT
public:
    explicit SenderEOFView(QWidget *parent = 0);
    ~SenderEOFView();
    int appendCRC(char *data, int size);
    bool isCalcCRC();
private:
    QComboBox *cbTypeCRC;
    QCheckBox *cbCheckCRC;
    QCheckBox *cbCheckCR;
    QCheckBox *cbCheckLF;
    QHBoxLayout *vlay;
signals:
    
public slots:
};

#endif // SENDEREOFVIEW_H
