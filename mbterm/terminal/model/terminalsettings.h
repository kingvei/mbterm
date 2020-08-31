#ifndef TERMINALSETTINGS_H
#define TERMINALSETTINGS_H

#include <QObject>
#include <QSettings>

class TerminalSettings : public QObject
{
    Q_OBJECT
public:
    explicit TerminalSettings(QObject *parent = nullptr);
private:
    QSettings m_settings;

signals:


};

#endif // TERMINALSETTINGS_H
