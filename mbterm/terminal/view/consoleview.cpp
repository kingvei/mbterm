#include "consoleview.h"
#include <QScrollBar>
#include <QDebug>

ConsoleView::ConsoleView(QList<QWidget *> *list, QWidget *parent) : QWidget(parent), displayAs(NULL)
{
    
    vlay = new QHBoxLayout;
    textEdit = new QPlainTextEdit;
    textEdit->setReadOnly(true);
    textEdit->setStyleSheet("background-color: black;" 
                            "font: bold 14px;"
                            "color: yellow;");
    textEdit->setMinimumWidth(500);
    vlay->addWidget(textEdit);
    consoleDisplayView = new ConsoleDisplayView();
    connect(consoleDisplayView, SIGNAL(released(DisplayDelegate*)), SLOT(setDelegate(DisplayDelegate*)));
    setDelegate(consoleDisplayView->delegate());
    vlay->addWidget(consoleDisplayView);
    
    QList<QWidget*>::iterator it;
    for(it = list->begin(); it != list->end(); ++it)
    {
        setSpacing(*it);
        vlay->addWidget(*it);
    }
    setSpacing(consoleDisplayView);
    
    setLayout(vlay);
}

ConsoleView::~ConsoleView()
{
    delete textEdit;
    delete consoleDisplayView;
    delete vlay;
}

void ConsoleView::putByteArray(QByteArray data, QString color)
{
   /* QString text;
    if(displayAs != NULL)
    {
        text = displayAs->formatText(data.toStdString().c_str(), data.length());
    }
    else
    {
        text = QString(data);
    }
    QString cb = QString("<font color=\"%1\">").arg(color);
    QString ce = "</font>";
    
    textEdit->textCursor().insertHtml(cb + text + ce);
    textEdit->textCursor().insertText("\n");*/
    ConsoleView::putByteArray(data.toStdString().c_str(), data.length(), color);
}

void ConsoleView::putByteArray(const char *data, int size, QString color)
{
    QString text;
    if(displayAs != NULL)
    {
        text = displayAs->formatText(data, size);
    }
    else
    {
        text = QString(QByteArray(data, size));
    }
    
    QString cb = QString("<font face=\"Consolas\" color=\"%1\">").arg(color);
    QString ce = "</font>";
    
    
    textEdit->textCursor().insertHtml(cb + "<b>" + text + "</b>" + ce);
    textEdit->textCursor().insertText("\n");
    QScrollBar *sb = textEdit->verticalScrollBar();
    sb->setValue(sb->maximum());
}

void ConsoleView::setDisplayDelegate(DisplayDelegate *dsp)
{
    displayAs = dsp;
}

void ConsoleView::setSpacing(QWidget *w)
{
    QLayout *l;
    l = w->layout();
    l->setSpacing(1);
    l->setMargin(1);
    w->setLayout(l);
}

void ConsoleView::clear()
{
    textEdit->clear();
}

void ConsoleView::setDelegate(DisplayDelegate *dsp)
{
    setDisplayDelegate(dsp);
}
