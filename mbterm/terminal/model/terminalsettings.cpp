#include "terminalsettings.h"

TerminalSettings::TerminalSettings(QObject *parent) : QObject(parent),
    m_settings(QSettings::IniFormat, QSettings::UserScope, QLatin1String("mbterm"), QLatin1String("termconfig"))
{

}
