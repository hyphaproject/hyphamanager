#ifndef USERDATABASESETTINGS_H
#define USERDATABASESETTINGS_H

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QSettings>
#include <QtCore/QMutex>

#include "hyphamanagersettings.h"


class UserDatabaseSettings : public QObject
{
    Q_OBJECT
public:
    explicit UserDatabaseSettings(HyphaManagerSettings *managerSettings, QObject *parent = 0);
    ~UserDatabaseSettings();

    void save();
    QVariant getValue(const QString &key, const QVariant &defaultValue);
    void setValue(const QString &key, const QVariant &value);

    QString getDriver();
    QString getHost();
    QString getDatabase();
    QString getUser();
    QString getPassword();
    QString getTable();
    QString getAttributeUsername();
    QString getAttributeFirstname();
    QString getAttributeLastname();
    QString getAttributeMail();
    QString getAttributeDevices();

signals:

public slots:

private:

    HyphaManagerSettings * managerSettings;

};

#endif // USERDATABASESETTINGS_H
