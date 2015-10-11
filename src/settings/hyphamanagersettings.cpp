#include <QtCore/QFileInfo>
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>

#include "hyphamanagersettings.h"

HyphaManagerSettings::HyphaManagerSettings(QString configfile, QObject *parent) : QObject(parent)
{
    this->configfile = configfile;
}

HyphaManagerSettings::~HyphaManagerSettings()
{

}

void HyphaManagerSettings::createNewFile()
{
    settings = new QSettings(configfile, QSettings::IniFormat );
    settings->beginGroup("database");
    settings->setValue("driver", "QSQLITE");
    settings->setValue("host", "localhost");
    settings->setValue("database", ":memory:");
    settings->setValue("username", "user");
    settings->setValue("password", "password");
    settings->endGroup();
    settings->beginGroup("userdatabase");
    settings->setValue("driver", "LDAP");
    settings->setValue("host", "localhost");
    settings->setValue("database", "dc=blechuhr");
    settings->setValue("username", "cn=admin");
    settings->setValue("password", "password");
    settings->setValue("table", "ou=people");
    settings->setValue("attrUsername", "cn");
    settings->setValue("attrFirstname", "givenname");
    settings->setValue("attrLastname", "sn");
    settings->setValue("attrMail", "mail");
    settings->setValue("attrDevices", "registeredaddress");
    settings->endGroup();
    settings->beginGroup("email");
    settings->setValue("user", "anonymous");
    settings->setValue("host", "localhost");
    settings->setValue("password", "password");
    settings->endGroup();
    save();
}

void HyphaManagerSettings::load()
{
    if(QFileInfo(configfile).exists()){
        settings = new QSettings( configfile, QSettings::IniFormat );
    }else{
        createNewFile();
    }
}

void HyphaManagerSettings::save()
{
    settings->sync();
}

QVariant HyphaManagerSettings::getValue(const QString &key, const QVariant &defaultValue = QVariant() )
{
    return settings->value(key,defaultValue);
}

QVariant HyphaManagerSettings::getValue(const QString &group, const QString &key, const QVariant &defaultValue)
{
    settings->beginGroup(group);
    QVariant rValue = settings->value(key,defaultValue);
    settings->endGroup();
    return rValue;
}

void HyphaManagerSettings::setValue(const QString &group, const QString &key, const QVariant &value)
{
    settings->beginGroup(group);
    settings->setValue(key, value);
    settings->endGroup();

}
