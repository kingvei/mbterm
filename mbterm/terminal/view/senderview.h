#ifndef SENDERVIEW_H
#define SENDERVIEW_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>

#include "sendereofview.h"

class SenderView : public QWidget
{
    Q_OBJECT
public:
    explicit SenderView(QWidget *parent = 0);
    ~SenderView();
private:

private:
    QLayout *vlay;
    QPushButton *btnSend;
    QLineEdit *lineEdit;
    
    SenderEOFView *sEOF;
signals:
    void send(const char *data, int size);
private slots:
    void sendPackage();
public slots:
    
};

#endif // SENDERVIEW_H
