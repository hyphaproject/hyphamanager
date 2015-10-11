#include <QtCore/QFileInfo>
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>

#include "hyphamanagersettings.h"
#include "userdatabasesettings.h"

UserDatabaseSettings::UserDatabaseSettings(HyphaManagerSettings * managerSettings, QObject *parent) : QObject(parent)
{
    this->managerSettings = managerSettings;
}

UserDatabaseSettings::~UserDatabaseSettings()
{

}

void UserDatabaseSettings::save()
{
    managerSettings->save();
}

QVariant UserDatabaseSettings::getValue(const QString &key, const QVariant &defaultValue = QVariant() )
{
    return managerSettings->getValue("userdatabase", key, defaultValue);
}

void UserDatabaseSettings::setValue(const QString &key, const QVariant &value)
{
    managerSettings->setValue("userdatabase", key, value);
}

QString UserDatabaseSettings::getDriver()
{
    return getValue("driver", "LDAP").toString();
}

QString UserDatabaseSettings::getHost()
{
    return getValue("host", "localhost").toString();
}

QString UserDatabaseSettings::getDatabase()
{
    return getValue("database", "dc=blechuhr").toString();
}

QString UserDatabaseSettings::getUser()
{
    return getValue("username", "cn=admin").toString();
}

QString UserDatabaseSettings::getPassword()
{
    return getValue("password", "password").toString();
}

QString UserDatabaseSettings::getTable()
{
    return getValue("table", "ou=people").toString();
}

QString UserDatabaseSettings::getAttributeUsername()
{
    return getValue("attrUsername", "cn").toString();
}

QString UserDatabaseSettings::getAttributeFirstname()
{
    return getValue("attrFirstname", "givenname").toString();
}

QString UserDatabaseSettings::getAttributeLastname()
{
    return getValue("attrLastname", "sn").toString();
}

QString UserDatabaseSettings::getAttributeMail()
{
    return getValue("attrMail", "mail").toString();
}

QString UserDatabaseSettings::getAttributeDevices()
{
    return getValue("attrDevices", "registeredaddress").toString();
}
