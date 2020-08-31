#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include <QWidget>
#include <QTextEdit>
#include <QLayout>
#include <QPlainTextEdit>

#include "display/displaydelegate.h"
#include "consoledisplayview.h"


class ConsoleView : public QWidget
{
    Q_OBJECT
public:
    explicit ConsoleView(QList<QWidget*> *list, QWidget *parent = 0);
    ~ConsoleView();
    void putByteArray(QByteArray data, QString color = "yellow");
    void putByteArray(const char *data, int size,  QString color = "yellow");
    void setDisplayDelegate(DisplayDelegate *dsp);
    void setSpacing(QWidget *w);
    void clear();
private:
    QPlainTextEdit *textEdit;
    QLayout *vlay;
    DisplayDelegate *displayAs;
    ConsoleDisplayView *consoleDisplayView;
    
signals:
    
public slots:
    void setDelegate(DisplayDelegate *dsp);
};

#endif // CONSOLEVIEW_H
