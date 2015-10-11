#include <QtCore/QFileInfo>
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>

#include "hyphamanagersettings.h"
#include "databasesettings.h"

DatabaseSettings::DatabaseSettings(HyphaManagerSettings *managerSettings, QObject *parent) : QObject(parent)
{
    this->managerSettings = managerSettings;
}

DatabaseSettings::~DatabaseSettings()
{

}

void DatabaseSettings::save()
{
    managerSettings->save();
}

QVariant DatabaseSettings::getValue(const QString &key, const QVariant &defaultValue = QVariant() )
{
    return managerSettings->getValue("database", key, defaultValue);
}

void DatabaseSettings::setValue(const QString &key, const QVariant &value)
{
    managerSettings->setValue("database", key, value);
}

QString DatabaseSettings::getDriver()
{
    return getValue("driver", "QSQLITE").toString();
}

QString DatabaseSettings::getHost()
{
    return getValue("host", "localhost").toString();
}

QString DatabaseSettings::getDatabase()
{
    return getValue("database", ":memory:").toString();
}

QString DatabaseSettings::getUser()
{
    return getValue("username", "hypha").toString();
}

QString DatabaseSettings::getPassword()
{
    return getValue("password", "hypha").toString();
}
